/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:53:36 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/25 19:27:13 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env ls executes ls and ignores env

#include "minishell.h"

int	env_builtin(t_minishell *data, t_tree *leaf)
{
	int	i;

	i = 0;
	if (leaf)
	{
		ft_putstr_fd(ENV_PREFIX, 2);
		ft_putstr_fd(leaf->content, 2);
		ft_putstr_fd(ENV_SUFFIX, 2);
		return (EXIT_FAILURE);
	}
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i], 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
