/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 08:51:36 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/13 08:52:31 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_right_node(t_tree *node, char **splitted, int *i)
{
	node->right->left = NULL;
	node->right->right = NULL;
	node->right->content = ft_strdup(splitted[*i]);
	node->file_fd = 0;
	node->right->type = WORD;
	node->right->visited = false;
	node->q_type = UNQUOTED;
	node->right->subshell_level = node->subshell_level;
}

void	append_splitted_tokens(t_tree *node, char **splitted)
{
	t_tree	*tmp;
	t_tree	*nxt;
	int		i;

	i = 1;
	if (node->content)
		free(node->content);
	node->content = ft_strdup(splitted[0]);
	tmp = node;
	nxt = node->right;
	while (splitted[i])
	{
		tmp->right = malloc(sizeof(*tmp));
		if (!tmp->right)
		{
			free_ar((void **)splitted);
			return ;
		}
		init_right_node(tmp, splitted, &i);
		tmp = tmp->right;
		i++;
	}
	tmp->right = nxt;
	free_ar((void **)splitted);
}
