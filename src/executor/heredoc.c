/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:03:33 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/18 15:11:03 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_errors(t_minishell *data, t_tree *node, char type)
{
	if (type == 'o')
	{
		perror("error creating temp file");
		if (data->exec.pipeline_child)
			exit_msh(data, 1);
	}
	else if (type == 'l')
	{
		if (g_sig)
			return (1);
		ft_putstr_fd(HERE_DOC_ERROR_PREFIX, 2);
		if (!node->right->content || node->right->type != WORD)
			ft_putstr_fd(node->right->left->content, 2);
		else
			ft_putstr_fd(node->right->content, 2);
		ft_putstr_fd(HERE_DOC_ERROR_SUFFIX, 2);
	}
	return (1);
}

void	heredoc_loop(t_minishell *data, t_tree *node, t_tree *del, char *p_line)
{
	char	*line;

	line = NULL;
	init_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			manage_errors(data, node, 'l');
			break ;
		}
		if (!ft_strncmp(del->content, line, ft_strlen(del->content) + 1))
			break ;
		p_line = expand_heredoc(line, del, data);
		free(line);
		line = NULL;
		ft_putstr_fd(p_line, node->file_fd);
		ft_putstr_fd("\n", node->file_fd);
		free(p_line);
		p_line = NULL;
	}
	init_interactive_signals('h');
	if (line)
		free(line);
}

static int	create_tempfile(char *filename)
{
	int		fd;
	int		i;
	int		tries;
	char	buf[32];

	tries = 5;
	while (tries-- > 0)
	{
		i = -1;
		fd = open("/dev/urandom", O_RDONLY);
		if (fd < 0)
			return (-1);
		if (read(fd, buf, sizeof(buf)) != sizeof(buf))
			return (close(fd), -1);
		close(fd);
		while (++i < 31)
			filename[i] = HEXMAP[buf[i % sizeof(buf)] % 62];
		filename[i] = '\0';
		fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
			return (fd);
	}
	return (-1);
}

int	heredoc_init(t_minishell *data, t_tree *node, t_tree *delim)
{
	char	*parsed_line;
	char	filename[32];

	parsed_line = NULL;
	node->file_fd = create_tempfile(filename);
	if (node->file_fd < 0)
		return (manage_errors(data, node, 'o'));
	heredoc_loop(data, node, delim, parsed_line);
	close(node->file_fd);
	node->file_fd = open(filename, O_RDONLY);
	if (node->file_fd < 0)
		return (manage_errors(data, node, 'o'));
	unlink(filename);
	if (parsed_line)
		free(parsed_line);
	return (0);
}

int	search_heredoc(t_minishell *data, t_tree *node)
{
	t_tree	*delim;

	if (!node)
		return (0);
	node->file_fd = -1;
	if (node->type == HERE_DOC)
	{
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
		heredoc_init(data, node, delim);
		if (g_sig)
			return (0);
	}
	search_heredoc(data, node->left);
	search_heredoc(data, node->right);
	return (0);
}
