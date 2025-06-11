/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:57 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/11 17:43:22 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_tree(t_token_list *list)
{
	t_token_list	*tmp;

	if (!list)
		return (NULL);
	tmp = list;
	while (tmp)
	{
		if (tmp->token_type == PIPE)
			return (split_and_build(tmp, list, PIPE));
		tmp = tmp->next;
	}
	tmp = list;
	while (tmp)
	{
		if (tmp->token_type == R_IN || tmp->token_type == R_OUT 
				|| tmp->token_type == AP_R_OUT 
				|| tmp->token_type == HERE_DOC)
				return (split_and_build(tmp, list, tmp->token_type));
		tmp = tmp->next;
	}
	return (build_word_node(list));
}

int	parser(t_token_list *list)
{
	t_tree	*root;

	root  = build_tree(list);
	if (!root)
		return (-1);
	return (0);
}
