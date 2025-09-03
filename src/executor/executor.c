/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:24:02 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/03 19:44:34 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_executor(t_minishell *data, t_tree *root)
{
	close_heredoc(data->root);
	free_ar((void **)data->exec.spath);
	data->exec.spath = NULL;
	data->exec.redir_num = 0;
	free_tree(root);
	data->root = NULL;
	if (restore_fd(data->exec.parent_fd_in, data->exec.curr_fd_in) == 1)
		return (1);
	if (restore_fd(data->exec.parent_fd_out, data->exec.curr_fd_out) == 1)
		return (1);
	return (0);
}

int	process_node(t_minishell *data, t_tree *node)
{
	node->visited = true;
	if (!node || (node && node->content && !node->content[0]))
	{
		if (data->exec.pipeline_child)
			exit_msh(data, 127);
		return (ft_putstr_fd("minishell: : command not found\n", 2), 127);
	}
	else if (node->subshell_level > data->exec.subshell_lvl)
		return(subshell(data, node));
	else if (node->type == PIPE)
		return (run_pipeline(data, node));
	else if (node->type == R_IN)
		return (redir_in(data, node));
	else if (node->type == R_OUT)
		return (redir_out(data, node));
	else if (node->type == AP_R_OUT)
		return (redir_out(data, node));
	else if (node->type == HERE_DOC)
		return (redir_in(data, node));
	else if (node->type == AND)
		return (logical_and(data, node));
	else if (node->type == OR)
		return (logical_or(data, node));
	else
		return (process_command(data, node));
}

int	executor(t_minishell *data, t_tree *root)
{
	int		ret;

	data->root = root;
	data->exec.spath = ft_split(fetch_val(data->envp, "PATH"), ':');
	search_heredoc(data, root);
	if (sig)
	{
		close_executor(data, root);
		return (130);
	}
	ret = process_node(data, root);
	if (data->exec.pipeline_child)
		exit_msh(data, ret);
	if (close_executor(data, root))
		ret = 1;
	return(ret);
}
