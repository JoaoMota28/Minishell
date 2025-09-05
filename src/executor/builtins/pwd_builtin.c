/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:19:11 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/05 12:30:42 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_minishell *data, t_tree *leaf)
{
	char	*pwd;
	int		internal_var;

	(void)leaf;
	internal_var = 1;
	pwd = data->pwd;
	if (!pwd)
	{
		internal_var = 0;
		pwd = getcwd(NULL, 0);
	}
	if (!pwd)
	{
		if (data->exec.pipeline_child)
			exit_msh(data, EXIT_FAILURE);
		ft_putstr_fd(PWD_ERROR, 2);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, 1);
	if (internal_var == 0)
		free (pwd);
	return (EXIT_SUCCESS);
}
