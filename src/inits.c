/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:54 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/16 18:12:06 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_init(t_minishell *data)
{
	data->exec.spath = NULL;
	data->exec.redir_num = 0;
	data->exec.curr_fd_in = STDIN_FILENO;
	data->exec.curr_fd_out = STDOUT_FILENO;
	data->exec.parent_fd_in = dup(STDIN_FILENO);
	data->exec.parent_fd_out = dup(STDOUT_FILENO);
	if (data->exec.parent_fd_out < 0 || data->exec.parent_fd_in < 0)
	{
		perror("Error duplicating standard fd");
		return (1);
	}
	data->exec.pid_count = 0;
	data->exec.pipeline_child = false;
	return (0);
}

void	data_init(t_minishell *data, char **envp)
{
	data->envp = dp_dup(envp);
	data->export = dp_dup(envp);
	if (!fetch_val(data->export, "OLDPWD"))
      add_val(&data->export, "OLDPWD", "");
	insertion_sort(data->export);
	data->prompt = PROMPT;
	data->pwd = getcwd(NULL, 0);
	data->oldpwd = NULL;
	data->root = NULL;
	exec_init(data);
	data->exit_code = 0;
}
