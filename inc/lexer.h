/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:33:08 by bpires-r          #+#    #+#             */
/*   Updated: 2025/05/29 15:46:47 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../complete_lib/42_Libft/libft.h"
# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Printf/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# define SYNTAX_ERROR_PIPE "Minishell: syntax error near unexpected token `|'\n"
# define SYNTAX_ERROR_R_IN "Minishell: syntax error near unexpected token `<'\n"
# define SYNTAX_ERROR_R_OUT "Minishell: syntax error near unexpected token `>'\n"
# define SYNTAX_ERROR_AP_R_OUT "Minishell: syntax error near unexpected token `>>'\n"
# define SYNTAX_ERROR_HEREDOC "Minishell: syntax error near unexpected token `<<'\n"
# define SYNTAX_ERROR_OPEN_SQUOTE "Minishell: syntax error unclosed single quote\n"
# define SYNTAX_ERROR_OPEN_DQUOTE "Minishell: syntax error unclosed double quotes\n"

typedef enum e_token_type
{
	PIPE,
	R_IN,
	R_OUT,
	AP_R_OUT,
	HERE_DOC,
	WORD,
}				t_token_type;

typedef enum e_quote_type
{
	UNQUOTED,
	SINGLE_O,
	DOUBLE_O,
}				t_quote_type;

typedef struct s_token_list
{
	char                *content;
	struct s_token_list *next;
	t_token_type		token_type;
}               t_token_list;

/// @brief Main Function that turns the parameter given into a list of tokens
/// @param line interactive line written by the minishell
/// @return exit status to the next step -> Parser
int lexer(char *line);

//Checks
t_quote_type	is_unquoted(char *line);
int				check_pipe_syntax_errors(t_token_list *token, t_token_list *prev);
int				check_redir_syntax_errors(t_token_list *token);
int				check_syntax_errors(t_token_list *list);

//Errors
void	put_unclosed_syntax_error(t_quote_type type);
void	put_token_syntax_error(t_token_list *token);

//Memory handle
void	free_tokens(t_token_list *list);

#endif
