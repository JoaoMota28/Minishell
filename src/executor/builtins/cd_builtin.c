/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:43:27 by jomanuel          #+#    #+#             */
/*   Updated: 2025/10/03 01:43:17 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_pwd(t_minishell *data, char *update, int flag)
{
	if (flag == 1)
	{
		if (fetch_val(data->envp, "OLDPWD"))
			replace_val(&data->envp, "OLDPWD", update);
		else if (fetch_val(data->export, "OLDPWD"))
			add_val(&data->envp, "OLDPWD", update, -1);
		replace_val(&data->export, "OLDPWD", update);
	}
	else
	{
		if (fetch_val(data->envp, "OLDPWD"))
			replace_val(&data->envp, "OLDPWD", update);
		else if (fetch_val(data->export, "OLDPWD"))
			add_val(&data->envp, "OLDPWD", update, -1);
		replace_val(&data->export, "OLDPWD", update);
	}
	replace_val(&data->envp, "PWD", data->pwd);
	replace_val(&data->export, "PWD", data->pwd);
}

void	update_internal_pwd(t_minishell *data)
{
	char	*newpwd;
	char	*prevpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cd: getpwd");
		return ;
	}
	if (fetch_val(data->envp, "PWD"))
		prevpwd = ft_strdup(fetch_val(data->envp, "PWD"));
	else
		prevpwd = ft_strdup(data->pwd);
	if (data->pwd)
		free(data->pwd);
	data->pwd = newpwd;
	if (!data->oldpwd)
		update_env_pwd(data, NULL, 1);
	else
		update_env_pwd(data, prevpwd, 0);
	free(data->oldpwd);
	data->oldpwd = prevpwd;
}

int	cd_chdir(t_minishell *data, t_tree *leaf, char *path)
{
	(void)leaf;
	if (!chdir(path))
		update_internal_pwd(data);
	else
	{
		ft_putstr_fd(CD_PREFIX, 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	cd_builtin(t_minishell *data, t_tree *leaf)
{
	char	*path;

	if (data->exec.pipeline_child)
		return (0);
	if (!leaf)
	{
		path = fetch_val(data->envp, "HOME");
		if (!path)
			return (ft_putstr_fd(CD_HOME, 2), EXIT_FAILURE);
	}
	else
	{
		if (leaf->right)
			return (ft_putstr_fd(CD_ARGS, 2), EXIT_FAILURE);
		path = leaf->content;
		if (!ft_strcmp(leaf->content, "-"))
		{
			path = data->oldpwd;
			if (!path)
				return (ft_putstr_fd(CD_OLDPWD, 2), EXIT_FAILURE);
			ft_putendl_fd(path, 1);
		}
	}
	return (cd_chdir(data, leaf, path));
}
