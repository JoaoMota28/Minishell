/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:16:06 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/11 22:04:34 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_heredoc(t_minishell *data, t_tree *node)
{
	if (!node)
		return (0);
	if (node->type == HERE_DOC && node->file_fd != data->exec.curr_fd_in)
		close(node->file_fd);
	close_heredoc(data, node->left);
	close_heredoc(data, node->right);
	return (0);
}

void	free_tree(t_tree *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->content && node->type == WORD)
		free(node->content);
	free(node);
}

void	free_msh(t_minishell *data)
{
	if (data->envp)
		free_ar((void **)data->envp);
	data->envp = NULL;
	if (data->export)
		free_ar((void **)data->export);
	data->export = NULL;
	if (data->pwd)
		free(data->pwd);
	data->pwd = NULL;
	if (data->oldpwd)
		free(data->oldpwd);
	data->oldpwd = NULL;
	if (data->root)
		free_tree(data->root);
	data->root = NULL;
	if (data->exec.spath)
		free_ar((void **)data->exec.spath);
	data->exec.spath = NULL;
}

void	exit_msh(t_minishell *data, int exit_code)
{
	close_parent_fds(data);
	close_heredoc(data, data->root);
	free_msh(data);
	if (data->exec.curr_fd_in != 0)
		close(data->exec.curr_fd_in);
	if (data->exec.curr_fd_out != 1)
		close(data->exec.curr_fd_out);
	exit(exit_code);
}
