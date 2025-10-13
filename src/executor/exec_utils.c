/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:15:03 by jomanuel          #+#    #+#             */
/*   Updated: 2025/10/13 01:31:53 by bpires-r         ###   ########.fr       */
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
		return (ft_strdup(node->content));
	data->exec.spath = ft_split(fetch_val(data->envp, "PATH"), ':');
	if (!data->exec.spath)
		return (NULL);
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
		if (*node->content || node->q_type != UNQUOTED)
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
	if (!cmd)
		return (NULL);
	while (node)
	{
		node->visited = true;
		if (*node->content || node->q_type != UNQUOTED)
			cmd[++i] = ft_strdup(node->content);
		node = node->right;
	}
	cmd[++i] = NULL;
	return (cmd);
}

int	restore_fd(int src, int dest)
{
	if (dup2(src, dest) == -1)
	{
		perror("Error restoring standard fds");
		return (1);
	}
	else
		return (0);
}

void	close_parent_fds(t_minishell *data)
{
	if (data->exec.par_fd_in != -1)
	{
		close(data->exec.par_fd_in);
		data->exec.par_fd_in = -1;
	}
	if (data->exec.par_fd_out != -1)
	{
		close(data->exec.par_fd_out);
		data->exec.par_fd_out = -1;
	}
}
