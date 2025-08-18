/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:09:05 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/18 18:21:48 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	logical_and(t_minishell *data, t_tree *node)
{
	int		ret;

	ret = process_node(data, node->left);
	if (ret == 0)
		ret = process_node(data, node->right);
	return (ret);
}

int	logical_or(t_minishell *data, t_tree *node)
{
	int		ret;

	ret = process_node(data, node->left);
	if (ret == 0)
		return (ret);
	else
		ret = process_node(data, node->right);
	return (ret);
}
