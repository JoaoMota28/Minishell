/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:12:16 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/22 23:05:03 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int manage_errors(t_minishell *data, char type)
{
    if (type == 'p')
    {
        perror("pipe error");
        if (data->exec.pipeline_child)
            exit_msh(data, 1);
    }
    else if (type == 'f')
    {
        perror("fork error");
        if (data->exec.pipeline_child)
            exit_msh(data, 1);
    }
    else if (type == 'd')
    {
        perror("dup error");
        close(data->exec.pipefd[0]);
        exit_msh(data, 1);
    }
    return (1);
}

int run_parent(t_minishell *data, pid_t last_pid)
{
    pid_t   pid;
    int     status;
    int     wstatus;

    status = 0;
    init_ignore_signals();
    restore_fd(data->exec.parent_fd_in, data->exec.curr_fd_in);
    restore_fd(data->exec.parent_fd_out, data->exec.curr_fd_out);
    while (true)
    {
        pid = waitpid(-1, &wstatus, 0);
        if (pid == last_pid)
            status = wstatus;
        if (pid < 0)
            break ;
    }
    init_interactive_signals();
    if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int run_last_pipe(t_minishell *data, t_tree *node)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        return (manage_errors(data, 'f'));
    if (pid == 0)
    {
        init_child_signals();
        data->exec.pipeline_child = true;
        restore_fd(data->exec.parent_fd_out, data->exec.curr_fd_out);
        process_node(data, node->right);
    }
    return (run_parent(data, pid));
}

void run_child(t_minishell *data, t_tree *node)
{
    init_child_signals();
    data->exec.pipeline_child = true;
    close(data->exec.pipefd[0]);
    if (dup2(data->exec.pipefd[1], data->exec.curr_fd_out) == -1)
        manage_errors(data, 'd');
    close(data->exec.pipefd[1]);
    process_node(data, node->left);
}

int run_pipeline(t_minishell *data, t_tree *node)
{
    pid_t   pid;

    data->exec.pipefd[0] = -1;
	data->exec.pipefd[1] = -1;
    while (true)
    {
        if (pipe(data->exec.pipefd) == -1) 
            return (manage_errors(data, 'p'));
        pid = fork();
        if (pid == -1)
            return (manage_errors(data, 'f'));
        if (pid == 0)
            run_child(data, node);
        if (data->exec.curr_fd_in != data->exec.parent_fd_in)
            close(data->exec.curr_fd_in);
        close(data->exec.pipefd[1]);
        if (dup2(data->exec.pipefd[0], data->exec.curr_fd_in) == -1)
            return (manage_errors(data, 'd'));
        close(data->exec.pipefd[0]);
        if (node->right->type == PIPE)
            node = node->right;
        else
            break ;
    }
    return (run_last_pipe(data, node));
}
