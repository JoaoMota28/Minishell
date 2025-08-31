/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:32:22 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/31 14:33:12 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_word_node(t_token_list *list, int level, int max_level)
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
	node->quote_type = list->quote_type;
	node->subshell_level = list->subshell_level;
	right = list->next;
	free(list->content);
	free(list);
	node->left = NULL;
	node->right = build_tree(right, level, max_level);
	node->visited = false;
	return (node);
}

t_tree	*split_and_build(t_token_list *target, t_token_list *left, t_token_type type, int level, int max_level)
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
	node->quote_type = target->quote_type;
	node->subshell_level = target->subshell_level;
	free (target);
	node->left = build_tree(left, level, max_level);
	node->right = build_tree(right, level, max_level);
	node->visited = false;
	return (node);
}

void print_tree(t_tree *node, int level, char *leaf)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
    if (leaf){
        printf("%s -> subshell_level: %d", leaf, node->subshell_level);
    }
    printf("[%s]\n", node->content);
	print_tree(node->left, level + 1, "left : ");
	print_tree(node->right, level + 1, "right : ");
}
