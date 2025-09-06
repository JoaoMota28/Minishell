/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:32:22 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/06 16:13:03 by jomanuel         ###   ########.fr       */
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

static void	init_splitted_node(t_token_list *t, t_tree *node)
{
	node->type = t->token_type;
	node->content = t->content;
	node->quote_type = t->quote_type;
	node->subshell_level = t->subshell_level;
}

t_tree	*split_and_build(t_token_list *t, t_token_list *lft, int lvl, int m_lvl)
{
	t_token_list	*right;
	t_tree			*node;
	t_token_list	*tmp;

	right = t->next;
	t->next = NULL;
	if (lft == t)
		lft = NULL;
	else
	{
		tmp = lft;
		while (tmp->next && tmp->next != t)
			tmp = tmp->next;
		tmp->next = NULL;
	}
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	init_splitted_node(t, node);
	free (t);
	node->left = build_tree(lft, lvl, m_lvl);
	node->right = build_tree(right, lvl, m_lvl);
	node->visited = false;
	return (node);
}

/*void print_tree(t_tree *node, int level, char *leaf)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
    if (leaf){
        printf("%s -> quote type: %d", leaf, node->quote_type);
    }
    printf("[%s]\n", node->content);
	print_tree(node->left, level + 1, "left : ");
	print_tree(node->right, level + 1, "right : ");
}*/
