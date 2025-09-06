/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:57:21 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/06 14:24:16 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_error(char *path, char **cmd, int errnum)
{
	struct stat	st;

	if (ft_strchr(cmd[0], '/') && errnum == EACCES)
	{
		ft_putstr_fd(cmd[0], 2);
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			ft_putstr_fd(": Is a directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (errnum == ENOENT)
	{
		if (ft_strchr(cmd[0], '/') != NULL)
		{
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
}

int	exec_command(t_minishell *data, t_tree *node)
{
	char	*path;
	char	**cmd;
	int		status;

	path = test_cmd(data, node);
	if (!path || !ft_strcmp(node->content, ".."))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->content, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (free(path), exit_msh(data, 127), 127);
	}
	if (!ft_strcmp(node->content, "."))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		return (free(path), exit_msh(data, 2), 2);
	}
	cmd = get_cmd_line(node);
	execve(path, cmd, data->envp);
	execve_error(path, cmd, errno);
	if (errno == ENOENT)
		status = 127;
	else
		status = 126;
	return (free(path), free_ar((void **) cmd), exit_msh(data, status), status);
}

static void	child_process(t_minishell *data, t_tree *node)
{
	init_child_signals();
	data->exec.pipeline_child = true;
	close_heredoc(data, data->root);
	exec_command(data, node);
}

int	fork_command(t_minishell *data, t_tree *node)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 1);
	if (pid == 0)
	{
		child_process(data, node);
	}
	init_ignore_signals();
	if (!data->exec.pipeline_child)
	{
		restore_fd(data->exec.par_fd_in, data->exec.curr_fd_in);
		restore_fd(data->exec.par_fd_out, data->exec.curr_fd_out);
	}
	waitpid(pid, &wstatus, 0);
	init_interactive_signals('i');
	handle_child_sig(wstatus);
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (1);
}

int	process_command(t_minishell *data, t_tree *node)
{
	if (!node->content)
	{
		if (data->exec.pipeline_child)
			exit_msh(data, 0);
		if (restore_fd(data->exec.par_fd_in, data->exec.curr_fd_in) == 1)
			return (1);
		if (restore_fd(data->exec.par_fd_out, data->exec.curr_fd_out) == 1)
			return (1);
		return (0);
	}
	expander(node, data);
	if (node->content[0] && !is_builtin(node))
		return (fork_command(data, node));
	else
	{
		if (data->exec.pipeline_child)
			close_parent_fds(data);
		return (exec_builtin(data, node));
	}
	return (1);
}
