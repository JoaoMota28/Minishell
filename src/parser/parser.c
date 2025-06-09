/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:57 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/06 19:28:29 by bpires-r         ###   ########.fr       */
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
