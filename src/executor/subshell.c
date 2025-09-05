/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 23:37:49 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/05 19:10:18 by jomanuel         ###   ########.fr       */
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
	waitpid(pid, &wstatus, 0);
	init_interactive_signals('i');
	handle_child_sig(wstatus);
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (1);
}
