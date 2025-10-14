/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:32:22 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/14 19:28:28 by bpires-r         ###   ########.fr       */
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
	node->subshell_level = list->subshell_level;
	right = list->next;
	free(list->content);
	free(list);
	node->left = NULL;
	node->right = build_tree(right, level, max_level);
	node->visited = false;
	node->q_type = UNQUOTED;
	return (node);
}

static void	init_splitted_node(t_token_list *t, t_tree *node)
{
	node->type = t->token_type;
	node->content = t->content;
	node->subshell_level = t->subshell_level;
	node->q_type = UNQUOTED;
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

t_tree	*clone_tree(const t_tree *src)
{
	t_tree	*dst;

	if (!src)
		return (NULL);
	dst = malloc(sizeof(t_tree));
	if (!dst)
		return (NULL);
	dst->content = NULL;
	if (src->content)
		dst->content = ft_strdup(src->content);
	dst->type = src->type;
	dst->subshell_level = src->subshell_level;
	dst->visited = src->visited;
	dst->left = NULL;
	dst->file_fd = src->file_fd;
	dst->right = clone_tree(src->right);
	return (dst);
}

void	clean_tree(t_tree **node)
{
	t_tree	**pp;
	t_tree	*cur;

	pp = node;
	while (*pp)
	{
		cur = *pp;
		if (((!cur->content) || (!cur->content[0])) && !cur->q_type)
		{
			*pp = cur->right;
			free(cur->content);
			free(cur);
		}
		else
			pp = &cur->right;
	}
}

void print_tree(t_tree *node, int level, char *leaf)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
    if (leaf){
        printf("%s -> ", leaf);
    }
    printf("[%s]\n", node->content);
	print_tree(node->left, level + 1, "left : ");
	print_tree(node->right, level + 1, "right : ");
}
