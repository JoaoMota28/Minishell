/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:21:30 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/03 19:32:06 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define PWD_ERROR "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"

# define ENV_PREFIX "env: ‘"
# define ENV_SUFFIX "’: No such file or directory\n"

# define CD_ARGS "minishell: cd: too many arguments\n"
# define CD_HOME "minishell: cd: Home not set\n"
# define CD_OLDPWD "minishell: cd: OLDPWD not set\n"
# define CD_PREFIX "minishell: cd: "

# define EXIT_MAX "9223372036854775807"
# define EXIT_ABS_MIN "9223372036854775808"
# define EXIT_ARGS "minishell: exit: too many arguments\n"
# define EXIT_PREFIX "minishell: exit: "
# define EXIT_NON_NUMERIC ": numeric argument required\n"

# define EXPORT_PREFIX "minishell: export: `"
# define EXPORT_INVALID "': not a valid identifier\n"

# include "../complete_lib/42_Libft/libft.h"
# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Printf/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "parser.h"

typedef struct s_minishell  t_minishell;

// Main func
int	(*buitin_arr(char *command))(t_minishell *data, t_tree *leaf);
int	exec_builtin(t_minishell *data, t_tree *root);

// Builtins list
int	echo_builtin(t_minishell *data, t_tree *leaf);
int	pwd_builtin(t_minishell *data, t_tree *leaf);
int	env_builtin(t_minishell *data, t_tree *leaf);
int	cd_builtin(t_minishell *data, t_tree *leaf);
int	exit_builtin(t_minishell *data, t_tree *leaf);
int	unset_builtin(t_minishell *data, t_tree *leaf);
int	export_builtin(t_minishell *data, t_tree *leaf);

// Utils
char	*fetch_val(char **arr, char *search);
void	replace_val(char ***arr, char *key, char *val);
int		add_val(char ***arr, char *key, char *val);
void	remove_val(char ***arr, char *search);
void	insertion_sort(char **arr);
bool	is_builtin(t_tree *root);
int		is_within_llong(const char *str);

#endif
