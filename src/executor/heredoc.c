/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:03:33 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/23 01:29:10 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int manage_errors(t_minishell *data, t_tree *node, char type)
{
    if (type == 'p')
    {
        perror("pipe error");
        if (data->exec.pipeline_child)
            exit_msh(data, 1);
    }
    else if (type == 'l')
	{
		ft_putstr_fd(HERE_DOC_ERROR_PREFIX, 2);
		if (!node->right->content || node->right->type != WORD)
			ft_putstr_fd(node->right->left->content, 2);
		else
			ft_putstr_fd(node->right->content, 2);
		ft_putstr_fd(HERE_DOC_ERROR_SUFFIX, 2);
	}
    return (1);
}

int	heredoc(t_minishell *data, t_tree *node)
{
	char	*line;
	char	*parsed_line;
	char	*delim;

	data->exec.pipefd[0] = -1;
	data->exec.pipefd[1] = -1;
	if (pipe(data->exec.pipefd) == -1)
		return(manage_errors(data, node, 'p'));
	init_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			manage_errors(data, node, 'l');
			break ;
		}
		if (node->right->type != WORD)
		{
			delim = node->right->left->content;
			if (!ft_strncmp(delim, line, ft_strlen(delim)))
				break ;
			parsed_line = expand_heredoc(line, node->right->left, data);
		}
		else
		{
			delim = node->right->content;
			if (!ft_strncmp(delim, line, ft_strlen(delim)))
				break ;
			parsed_line = expand_heredoc(line, node->right, data);
		}
		free(line);
		line = NULL;
		ft_putstr_fd(parsed_line, data->exec.pipefd[1]);
		ft_putstr_fd("\n", data->exec.pipefd[1]);
		free(parsed_line);
		parsed_line = NULL;
	}
	if (line)
		free(line);
	if (parsed_line)
		free(parsed_line);
	close(data->exec.pipefd[1]);
	if (dup2(data->exec.pipefd[0], data->exec.curr_fd_in) == -1)
		return (close(data->exec.pipefd[0]), perror(IN_DUP_ERROR), 1);
	close(data->exec.pipefd[0]);
	init_interactive_signals();
	if (node->right && node->right->type != WORD)
		return (process_node(data, node->right));
	else if (node->right->right)
		return (process_node(data, node->right->right));
	return (0);
}
