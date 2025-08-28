/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:32:22 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/28 19:42:20 by bpires-r         ###   ########.fr       */
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
	node->quote_type = list->quote_type;
	right = list->next;
	free(list->content);
	free(list);
	node->left = NULL;
	node->right = build_tree(right);
	node->subshell = NULL;
	node->visited = false;
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
	node->quote_type = target->quote_type;
	free (target);
	node->left = build_tree(left);
	node->right = build_tree(right);
	node->subshell = NULL;
	node->visited = false;
	return (node);
}

t_token_list	*extract_subshell_tokens(t_token_list **list)
{
	int				level;
	t_token_list	*last;
	t_token_list	*tmp;
	t_token_list	*extracted;
	t_token_list	*next;
	t_token_list	*closing;

	tmp = *list;
	extracted = NULL;
	last = NULL;
	level = 1;
	next = NULL;
	while (tmp && level > 0)
	{
		//acho q da para usar o meu set type da subshell 
		//do lexer mas so quero por a funcionar first eu sei
		//eu sei q ta feio </3
		if (tmp->token_type == SUBSHELL && tmp->p_type == P_OPEN)
			level++;
		else if (tmp->token_type == SUBSHELL && tmp->p_type == P_CLOSED)
		{
			level--;
			if (!level)
			{
				closing = tmp;
				tmp = tmp->next;
				free(closing->content);
				free(closing);
				break ;
			}
		}
		if (level > 0)
		{
			next = tmp->next;
			tmp->next = NULL;
			if (!extracted)
				extracted = tmp;
			else
				last->next = tmp;
			last = tmp;
			tmp = next;
		}
	}
	*list = tmp;
	return (extracted);
}

void	set_subshell_level(t_tree *node, int level)
{
	if (!node)
		return ;
	node->subshell_level = level;
	set_subshell_level(node->left, level);
	set_subshell_level(node->right, level);
}

void print_tree(t_tree *node, int level, char *leaf)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
    if (leaf){
        printf("%s", leaf);
    }
    printf("[%s]\n", node->content);
	print_tree(node->left, level + 1, "left : ");
	print_tree(node->right, level + 1, "right : ");
}
