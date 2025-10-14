/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:30:41 by jomanuel          #+#    #+#             */
/*   Updated: 2025/10/14 22:05:31 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_fd(t_minishell *data, t_tree *node)
{
	char	*file;

	if (node->right->type != WORD && !node->right->visited)
	{
		expander(node->right->left, data);
		file = node->right->left->content;
		node->right->left->visited = true;
	}
	else if (!node->right->visited)
	{
		expander(node->right, data);
		file = node->right->content;
		node->right->visited = true;
	}
	if (node->type == R_IN)
		return (open(file, O_RDONLY));
	else if (node->type == R_OUT)
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (node->type == AP_R_OUT)
		return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		return (node->file_fd);
}

static int	dup_in(t_minishell *data, t_tree *node)
{
	int	new_fd;

	new_fd = open_fd(data, node);
	if (new_fd == -1)
		return (perror(IN_OPEN_ERROR), 1);
	if (dup2(new_fd, data->exec.curr_fd_in) == -1)
		return (close(new_fd), perror(IN_DUP_ERROR), 1);
	close(new_fd);
	if (node->right && node->right->type != WORD)
		return (process_node(data, node->right));
	return (0);
}

int	redir_in(t_minishell *data, t_tree *node)
{
	int		status;
	t_tree	*head;
	t_tree	*tail;

	head = NULL;
	tail = NULL;
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

static int	dup_out(t_minishell *data, t_tree *node)
{
	int	new_fd;

	new_fd = open_fd(data, node);
	if (new_fd == -1)
		return (perror(OUT_OPEN_ERROR), 1);
	if (dup2(new_fd, data->exec.curr_fd_out) == -1)
		return (close(new_fd), perror(OUT_DUP_ERROR), 1);
	close(new_fd);
	if (node->right && node->right->type != WORD)
		return (process_node(data, node->right));
	return (0);
}

int	redir_out(t_minishell *data, t_tree *node)
{
	int		status;
	t_tree	*head;
	t_tree	*tail;

	head = NULL;
	tail = NULL;
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
	return (status);
}
