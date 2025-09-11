/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:26:54 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/11 23:14:28 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../complete_lib/42_Libft/libft.h"
# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Printf/ft_printf.h"
# include "builtin.h"
# include <sys/stat.h>
# include <errno.h>

# define IN_OPEN_ERROR "Error opening infile"
# define OUT_OPEN_ERROR "Error opening outfile"
# define IN_DUP_ERROR "Error redirecting stdin"
# define OUT_DUP_ERROR "Error redirecting stdout"
# define HERE_DOC_ERROR_PREFIX "minishell: warning: here-document delimited \
by end-of-file (wanted \'"
# define HERE_DOC_ERROR_SUFFIX "\')\n"
# define SHLVL_ERROR_PREFIX "minishell: warning: shell level ("
# define SHLVL_ERROR_SUFFIX ") too high, resetting to 1\n"
# define HEXMAP "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

typedef struct s_minishell	t_minishell;

typedef struct s_exec
{
	char	**spath;
	int		par_fd_in;
	int		par_fd_out;
	int		curr_fd_in;
	int		curr_fd_out;
	int		pipefd[2];
	int		pid_count;
	int		redir_num;
	int		pipeline_child;
	int		subshell_lvl;
}	t_exec;

//processing
int		process_node(t_minishell *data, t_tree *node);
int		process_command(t_minishell *data, t_tree *node);
int		exec_command(t_minishell *data, t_tree *node);
int		redir_in(t_minishell *data, t_tree *node);
int		redir_out(t_minishell *data, t_tree *node);
int		run_pipeline(t_minishell *data, t_tree *pipe_root);
int		logical_and(t_minishell *data, t_tree *node);
int		logical_or(t_minishell *data, t_tree *node);
int		heredoc(t_minishell *data, t_tree *node);
int		subshell(t_minishell *data, t_tree *node);

//utils
char	*test_cmd(t_minishell *data, t_tree *node);
char	**get_cmd_line(t_tree *node);
int		restore_fd(int src, int dest);
void	close_parent_fds(t_minishell *data);
int		search_heredoc(t_minishell *data, t_tree *node);
int		close_heredoc(t_minishell *data, t_tree *node);
void	attach_to_cmd(t_tree *node, t_tree *head);
void	collect_to_list(t_tree *root, t_tree **head, t_tree **tail);

#endif