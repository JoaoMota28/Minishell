/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:43:51 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/09 17:35:48 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static t_token_list *new_token(const char *str, t_token_type type)
{
	t_token_list *node = malloc(sizeof(t_token_list));
	if (!node)
		return (NULL);
	node->content = strdup(str);
	node->token_type = type;
	node->next = NULL;
	return (node);
}

static t_token_list *append_token(t_token_list *head, t_token_list *token)
{
	if (!head)
		return (token);
	t_token_list *cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = token;
	return (head);
}

static void free_tree(t_tree *node)
{
	if (!node)
		return;
	free_tree(node->left);
	free_tree(node->right);
	if (node->content)
		free(node->content);
	free(node);
}

static void print_tree(t_tree *node, int level, char *leaf)
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

int	main(void)
{
    t_token_list *list = new_token("echo", WORD);
    list = append_token(list, new_token("hi", WORD));
    list = append_token(list, new_token("|", PIPE));
    list = append_token(list, new_token("wc", WORD));
    list = append_token(list, new_token("-l", WORD));
    list = append_token(list, new_token(">", R_OUT));
    list = append_token(list, new_token("out.txt", WORD));
    list = append_token(list, new_token("|", PIPE));
    list = append_token(list, new_token("grep", WORD));
    list = append_token(list, new_token("miau", WORD));
	printf("Test 1 : mixed “echo hi | wc -l > out.txt | grep miau”\n");
	t_tree *tree = build_tree(list);
	if (tree)
	{
		print_tree(tree, 0, NULL);
		free_tree(tree);
	}
    return (0);
}*/