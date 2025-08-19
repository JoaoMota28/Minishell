/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:54 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/19 19:50:45 by jomanuel         ###   ########.fr       */
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

char	**private_envp()
{
	char	**new_envp;
	char	*pwd;
	int		i;

	i = 0;
	new_envp = malloc(5 * sizeof(char *));
	if (!new_envp)
		return (NULL);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(new_envp), NULL);
	new_envp[i++] = ft_strjoin("PWD=", pwd);
	free(pwd);
	new_envp[i++] = ft_strdup("SHLVL=1");
	new_envp[i++] = ft_strjoin("PATH=", PRIVATE_PATH);
	new_envp[i++] = ft_strdup("_=/usr/bin/env");
	new_envp[i++] = NULL;
	return (new_envp);
}

void	data_init(t_minishell *data, char **envp)
{
	data->envp = dp_dup(envp);
	if (!data->envp || !data->envp[0])
		data->envp = private_envp(data);
	data->export = dp_dup(data->envp);
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
