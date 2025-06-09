/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:21:43 by bpires-r          #+#    #+#             */
/*   Updated: 2025/05/29 17:49:54 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../complete_lib/42_Libft/libft.h"
# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Printf/ft_printf.h"
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"

# define PROMPT "Minishell >$"
# define PRIVATE_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin\
:/usr/bin:/sbin:/bin"
# define WRONG_ARGC "Minishell: no arguments expected"

typedef struct s_minishell
{
	char	*prompt;
	int		exit_code;
}				t_minishell;

//inits
void    data_init(t_minishell *data);

//free and exit
void    exit_msh(t_minishell *data, int exit_code);

//utils
int 	is_space(char c);
int	is_operator(t_token_type type);

#endif