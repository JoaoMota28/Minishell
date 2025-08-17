/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:09:05 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/17 15:09:26 by jomanuel         ###   ########.fr       */
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