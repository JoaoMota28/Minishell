/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 08:51:36 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 11:33:28 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_right_node(t_tree *node, t_tree *new, char **splitted, int *i)
{
	new->left = NULL;
	new->right = NULL;
	new->content = ft_strdup(splitted[*i]);
	new->file_fd = 0;
	new->type = WORD;
	new->visited = false;
	new->q_type = UNQUOTED;
	new->subshell_level = node->subshell_level;
}

int	append_splitted_tokens(t_tree *node, char **splitted)
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
		tmp->right = ft_calloc(1, sizeof(*tmp));
		if (!tmp->right)
		{
			free_ar((void **)splitted);
			return (0);
		}
		init_right_node(tmp, tmp->right, splitted, &i);
		tmp = tmp->right;
		i++;
	}
	tmp->right = nxt;
	free_ar((void **)splitted);
	return (i - 1);
}
