/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:16:06 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/11 17:43:53 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tree(t_tree *node)
{
	if (!node)
		return;
	free_tree(node->left);
	free_tree(node->right);
	if (node->content)
		free(node->content);
	free(node);
}

void	exit_msh(t_minishell *data, int exit_code)
{
	if (data->envp)
	{
		free_ar((void **)data->envp);
		data->envp = NULL;
	}
	exit(exit_code);
}
