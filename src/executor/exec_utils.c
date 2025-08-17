/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:15:03 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/17 14:59:04 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*test_cmd(t_minishell *data, t_tree *node)
{
	char	*tmp;
	char	*cmd;
	int		i;

	tmp = NULL;
	cmd = NULL;
	i = 0;
	if (!node || !node->content)
		return (NULL);
	if (access(node->content, X_OK) == 0)
		return (node->content);
	while (data->exec.spath[i])
	{
		tmp = ft_strjoin(data->exec.spath[i], "/");
		cmd = ft_strjoin(tmp, node->content);
		free(tmp);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

int	count_nodes(t_tree *node)
{
	int	i;

	i = 0;
	while (node)
	{
		i++;
		node = node->right;
	}
	return (i);
}

char	**get_cmd_line(t_tree *node)
{
	char	**cmd;
	int		i;

	i = -1;
	cmd = NULL;
	cmd = malloc((count_nodes(node) + 1) * sizeof(char *));
	while (node)
	{
		cmd[++i] = ft_strdup(node->content);
		node = node->right;
	}
	cmd[++i] = NULL;
	return (cmd);
}

int	restore_fd(int src, int dest, char c)
{
	if (dup2(src, dest) == -1)
	{
		if (c == 'o')
			perror("Error restoring stdout");
		if (c == 'i')
			perror("Error restoring stdin");
		return (1);
	}
	else
		return (0);
}

void	close_parent_fds(t_minishell *data)
{
	if (data->exec.parent_fd_in != -1)
	{
		close(data->exec.parent_fd_in);
		data->exec.parent_fd_in = -1;
	}
	if (data->exec.parent_fd_out != -1)
	{
		close(data->exec.parent_fd_out);
		data->exec.parent_fd_out = -1;
	}
}
