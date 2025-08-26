/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:30:41 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/26 16:12:47 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_in(t_minishell *data, t_tree *node)
{
	int	new_fd;

	if (node->type == R_IN)
	{
		if (node->right->type != WORD)
		{
			new_fd = open(node->right->left->content, O_RDONLY);
			node->right->left->visited = true;
		}
		else
		{
			new_fd = open(node->right->content, O_RDONLY);
			node->right->visited = true;
		}
		if (new_fd == -1)
			return (perror(IN_OPEN_ERROR), 1);
	}
	else
		new_fd = node->pipe_hd[0];
	if (dup2(new_fd, data->exec.curr_fd_in) == -1)
		return (close(new_fd), perror(IN_DUP_ERROR), 1);
	close(new_fd);
	if (node->right && node->right->type != WORD)
		return (process_node(data, node->right));
	return (0);
}

int redir_in(t_minishell *data, t_tree *node)
{
    int	status;
	t_tree *head = NULL;
    t_tree *tail = NULL;

	data->exec.redir_num++;
	if (data->exec.redir_num == 1)
	{
		status = dup_in(data, node);
		if (status != 0)
			return (status);
		collect_to_list(node, &head, &tail);
    	attach_to_cmd(node, head);
		if (node->left)
			status = process_node(data, node->left);
	}
	else
		status = dup_in(data, node);
	return (status);
}

int dup_out(t_minishell *data, t_tree *node)
{
	int	new_fd;
	int	flags;

	if (node->type == AP_R_OUT)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (node->right->type != WORD)
	{
		new_fd = open(node->right->left->content, flags, 0644);
		node->right->left->visited = true;
	}
	else
	{
		new_fd = open(node->right->content, flags, 0644);
		node->right->visited = true;
	}
	if (new_fd == -1)
		return(perror(OUT_OPEN_ERROR), 1);
	if (dup2(new_fd, data->exec.curr_fd_out) == -1)
		return (close(new_fd), perror(OUT_DUP_ERROR), 1);
	close(new_fd);
	if (node->right && node->right->type != WORD)
    	return (process_node(data, node->right));
  	return (0);
}

int redir_out(t_minishell *data, t_tree *node)
{
	int status;
	t_tree *head = NULL;
    t_tree *tail = NULL;

	data->exec.redir_num++;
	if (data->exec.redir_num == 1)
	{
    	status = dup_out(data, node);
    	if (status != 0)
			return (status);
		collect_to_list(node, &head, &tail);
    	attach_to_cmd(node, head);
		if (node->left)
			status = process_node(data, node->left);
  	}
  	else
	  	status = dup_out(data, node);
  	return status;
}
