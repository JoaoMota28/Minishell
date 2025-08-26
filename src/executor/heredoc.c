/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:03:33 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/26 21:13:35 by jomanuel         ###   ########.fr       */
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

int	close_heredoc(t_tree *node)
{
	if (!node)
		return (0);
	if (node->type == HERE_DOC)
		close(node->pipe_hd[0]);
	close_heredoc(node->left);
	close_heredoc(node->right);
	return (0);
}

int	heredoc_loop(t_minishell *data, t_tree *node)
{
	char	*line;
	char	*parsed_line;
	t_tree	*delim;

	parsed_line = NULL;
	line = NULL;
	if (node->right->type != WORD)
	{
		delim = node->right->left;
		node->right->left->visited = true;
	}
	else
	{
		delim = node->right;
		node->right->visited = true;
	}
	init_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			manage_errors(data, node, 'l');
			break ;
		}
		parsed_line = expand_heredoc(line, delim, data);
		if (!ft_strncmp(delim->content, parsed_line, ft_strlen(delim->content) + 1))
			break ;
		free(line);
		line = NULL;
		ft_putstr_fd(parsed_line, node->pipe_hd[1]);
		ft_putstr_fd("\n", node->pipe_hd[1]);
		free(parsed_line);
		parsed_line = NULL;
	}
	init_interactive_signals();
	if (line)
		free(line);
	if (parsed_line)
		free(parsed_line);
	close(node->pipe_hd[1]);
	return (0);
}

int	search_heredoc(t_minishell *data, t_tree *node)
{
	if (!node)
		return (0);
	node->pipe_hd[0] = -1;
	node->pipe_hd[1] = -1;
	if (node->type == HERE_DOC)
	{
		if (pipe(node->pipe_hd) == -1)
			return(manage_errors(data, node, 'p'));
		heredoc_loop(data, node);
	}
	search_heredoc(data, node->left);
	search_heredoc(data, node->right);
	return (0);
}
