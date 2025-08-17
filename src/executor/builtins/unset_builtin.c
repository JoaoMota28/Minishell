/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:49:30 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/16 17:46:37 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_minishell *data, t_tree *leaf)
{
	if (!leaf)
		return (EXIT_SUCCESS);
	while (leaf)
	{
		remove_val(&data->export, leaf->content);
		remove_val(&data->envp, leaf->content);
		leaf = leaf->right;
	}
	return(EXIT_SUCCESS);
}
