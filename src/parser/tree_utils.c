/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:32:22 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/11 17:43:35 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_tree	*build_word_node(t_token_list *list)
{
	t_tree			*node;
	t_token_list	*right;

	if (!list)
		return (NULL);
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = WORD;
	node->content = ft_strdup(list->content);
	right = list->next;
	free(list->content);
	free(list);
	node->left = NULL;
	node->right = build_tree(right);
	node->subshell = NULL;
	node->visited = 0;
	return (node);
}

t_tree	*split_and_build(t_token_list *target, t_token_list *left, t_token_type type)
{
	t_token_list	*right;
	t_tree			*node;
	t_token_list	*tmp;

	right = target->next;
	target->next = NULL;
	if (left == target)
		left = NULL;
	else
	{
		tmp = left;
		while (tmp->next && tmp->next != target)
			tmp = tmp->next;
		tmp->next = NULL;
	}
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = type;
	node->content = target->content;
	free (target);
	node->left = build_tree(left);
	node->right = build_tree(right);
	node->subshell = NULL;
	node->visited = 0;
	return (node);
}

