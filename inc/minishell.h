/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:21:43 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/03 16:07:24 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include "../complete_lib/42_Libft/libft.h"
# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Printf/ft_printf.h"
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include "executor.h"

extern volatile sig_atomic_t	sig;

# define PROMPT "Minishell>$ "
# define PRIVATE_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin\
:/usr/bin:/sbin:/bin"
# define WRONG_ARGC "Minishell: no arguments expected"

typedef struct s_minishell
{
	char	*prompt;
	char	**envp;
	char	**export;
	char	*pwd;
	char	*oldpwd;
	t_tree	*root;
	t_exec	exec;
	int		exit_code;
}				t_minishell;

/// @brief Main Function that turns the parameter given into a list of tokens
/// @param line interactive line written by the minishell
/// @return exit status to the next step -> Parser
int 	lexer(char *line, t_minishell *data);
void	expander(t_tree *node, t_minishell *data);
int		parser(t_minishell *data, t_token_list *list);
int		executor(t_minishell *data, t_tree *root);

//expander
char	*expand_token(char *content, t_minishell *data);
int		get_exp_length(char *content, t_minishell *data);
char	*expand_heredoc(char *line, t_tree *delim, t_minishell *data);

//inits
void    data_init(t_minishell *data, char **envp);
void	init_signals(char type);

//free and exit
void    exit_msh(t_minishell *data, int exit_code);
void	free_tree(t_tree *node);

//signals
void	set_handler(int signum, void (*handler)(int), int flags);
void	handle_sigint_h(int signo);
void	handle_sigint_i(int signo);
void	handle_sigint_i2(int signo);
void	handle_child_sig(int signo);
void	init_interactive_signals();
void	init_interactive_signals2();
void	init_child_signals();
void	init_heredoc_signals();
void	init_ignore_signals();

//utils
int		is_operator(t_token_type type);
char	**dp_dup(char **dp);
int		dp_len(char **dp);
char	*get_env(char **envp, char *name);

#endif