/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 23:37:49 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/01 01:09:58 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	subshell(t_minishell *data, t_tree *node)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
        if (data->exec.pipeline_child)
            exit_msh(data, 1);
	}
	if (pid == 0)
	{
		init_child_signals();
		data->exec.subshell_lvl++;
    	exit_msh(data, process_node(data, node));
	}
	init_ignore_signals();
	//restore_fd(data->exec.parent_fd_in, data->exec.curr_fd_in);
    //restore_fd(data->exec.parent_fd_out, data->exec.curr_fd_out);
    waitpid(pid, &wstatus, 0);
    init_interactive_signals();
    handle_child_sig(wstatus);
    if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (1);
}
