/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:16:06 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/17 14:58:48 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tree(t_tree *node)
{
	if (!node)
		return;
	free_tree(node->left);
	free_tree(node->right);
	if (node->content)
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
	free(data->pwd);
	data->pwd = NULL;
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
	free_msh(data);
	close_parent_fds(data);
	if (data->exec.curr_fd_in != 0)
		close(data->exec.curr_fd_in);
	if (data->exec.curr_fd_out != 1)
		close(data->exec.curr_fd_out);
	exit(exit_code);
}
