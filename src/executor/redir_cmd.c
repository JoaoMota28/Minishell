/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:04:15 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/26 16:14:51 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tree	*right_chain_tail(t_tree *node)
{
	if (!node)
		return NULL;
	while (node->right)
		node = node->right;
	return node;
}

static void	mark_visited_subtree(t_tree *node)
{
    if (!node)
		return;
    node->visited = 1;
    mark_visited_subtree(node->left);
    mark_visited_subtree(node->right);
}

void	collect_to_list(t_tree *root, t_tree **head, t_tree **tail)
{
	t_tree	*det;

	if (!root)
		return;
	if (root->right && !root->right->visited)
	{
		det = root->right;
		root->right = NULL;
		if (!*head) 
		{
			*head = det;
			*tail = right_chain_tail(det);
		}
		else
		{
			(*tail)->right = det;
			*tail = right_chain_tail(det);
		}
		mark_visited_subtree(det);
	}
  	collect_to_list(root->left, head, tail);
  	collect_to_list(root->right, head, tail);
}

void attach_to_cmd(t_tree *node, t_tree *head)
{
	t_tree *tail;

  	if (!head)
		return;
  	if (!node->left)
    	node->left = head;
  	else
	{
    	tail = right_chain_tail(node->left);
    	tail->right = head;
  	}
}
