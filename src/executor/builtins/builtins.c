/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:11:09 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/04 17:19:26 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	(*buitin_arr(char *command))(t_minishell *data, t_tree *leaf)
{
	int			i;
	static void	*builtin[7][2] = {
	{"cd", cd_builtin},
	{"echo", echo_builtin},
	{"env", env_builtin},
	{"exit", exit_builtin},
	{"export", export_builtin},
	{"pwd", pwd_builtin},
	{"unset", unset_builtin}
	};

	i = 0;
	while (i < 7)
	{
		if (command)
		{
			if (!ft_strcmp(command, builtin[i][0]))
				return (builtin[i][1]);
		}
		i++;
	}
	return (NULL);
}

int	exec_builtin(t_minishell *data, t_tree *root)
{
	int	(*fn)(t_minishell *, t_tree *);
	int	status;

	status = 1;
	fn = buitin_arr(root->content);
	if (fn)
		status = fn(data, root->right);
	if (status == 0 && !data->exec.pipeline_child)
	{
		if (data->exec.par_fd_in != -1)
			if (restore_fd(data->exec.par_fd_in, data->exec.curr_fd_in) == 1)
				return (1);
		if (data->exec.par_fd_out != -1)
			if (restore_fd(data->exec.par_fd_out, data->exec.curr_fd_out) == 1)
				return (1);
	}
	return (status);
}

bool	is_builtin(t_tree *root)
{
	int	(*fn)(t_minishell *, t_tree *);

	fn = buitin_arr(root->content);
	if (fn)
		return (true);
	else
		return (false);
}
