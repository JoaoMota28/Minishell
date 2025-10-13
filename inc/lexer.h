/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:33:08 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/13 01:15:10 by bpires-r         ###   ########.fr       */
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
# define SYNTAX_ERROR_P_OPEN "Minishell: syntax error near \
unexpected token `('\n"
# define SYNTAX_ERROR_P_CLOSED "Minishell: syntax error near \
unexpected token `)'\n"
# define SYNTAX_ERROR_R_IN "Minishell: syntax error near unexpected token `<'\n"
# define SYNTAX_ERROR_R_OUT "Minishell: syntax error near \
unexpected token `>'\n"
# define SYNTAX_ERROR_AP_R_OUT "Minishell: syntax error near \
unexpected token `>>'\n"
# define SYNTAX_ERROR_HEREDOC "Minishell: syntax error near \
unexpected token `<<'\n"
# define SYNTAX_ERROR_AND "Minishell: syntax error near unexpected token `&&'\n"
# define SYNTAX_ERROR_OR "Minishell: syntax error near unexpected token `||'\n"
# define SYNTAX_ERROR_OPEN_SQUOTE "Minishell: syntax error \
unclosed single quote\n"
# define SYNTAX_ERROR_OPEN_DQUOTE "Minishell: syntax error \
unclosed double quotes\n"
# define SYNTAX_ERROR_OPEN_P "Minishell: syntax error unclosed parentheses\n"

typedef enum e_token_type
{
	PIPE,
	R_IN,
	R_OUT,
	AP_R_OUT,
	HERE_DOC,
	AND,
	OR,
	SUBSHELL,
	WORD,
}				t_token_type;

typedef enum e_p_type
{
	P_CLOSED,
	P_OPEN,
}				t_p_type;

typedef enum e_quote_type
{
	UNQUOTED,
	SINGLE_O,
	DOUBLE_O,
}				t_quote_type;

typedef struct s_token_list
{
	char				*content;
	struct s_token_list	*next;
	int					subshell_level;
	t_token_type		token_type;
	t_p_type			p_type;
}				t_token_list;

//Checks
t_quote_type	is_unquoted(char *line);
int				check_pipe_syntax_errors(t_token_list *token,
					t_token_list *prev);
int				check_redir_syntax_errors(t_token_list *token);
int				check_syntax_errors(t_token_list *list);
int				check_heredoc_syntax_errors(t_token_list *token);
int				check_and_or_syntax_errors(t_token_list *token,
					t_token_list *prev);
int				check_subshell_syntax_errors(t_token_list *token,
					t_token_list *prev);
int				check_unclosed(char *line);

//Utils
void			set_type(t_token_list *node, char *line, int *i);
t_quote_type	set_quote_type(char *line, int index);
t_quote_type	detect_quote_type(char *word);
t_p_type		check_balance_p(char *line);
void			assign_subshell(t_token_list *node, int *current_level);
t_token_list	*lex_node(char *line, int *i);

//Errors
void			put_unclosed_syntax_error(t_quote_type type,
					t_p_type parentheses);
void			put_token_syntax_error(t_token_list *token);

//Memory handle
void			free_tokens(t_token_list *list);

#endif
