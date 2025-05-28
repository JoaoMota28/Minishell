/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 16:56:20 by bpires-r          #+#    #+#             */
/*   Updated: 2025-05-28 16:56:20 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote_type	is_unquoted(char *line)
{
	t_quote_type	type;
	int				i;

	i = 0;
	type = UNQUOTED;
	while (line[i])
	{
		if (line[i] == '"' && type == UNQUOTED)
			type = DOUBLE_O;
		else if (line[i] == '"' && type == DOUBLE_O)
			type = UNQUOTED;
		else if (line[i] == '\'' && type == UNQUOTED)
			type = SINGLE_O;
		else if (line[i] == '\'' && type == SINGLE_O)
			type = UNQUOTED;
		i++;
	}
	return (type);
}

int	check_pipe_syntax_errors(t_token_list *token, t_token_list *prev)
{
	if (token->token_type == PIPE)
			if (!prev || !token->next 
				|| token->next->token_type == PIPE)
					return (1);
	return (0);
}

int	check_redir_syntax_errors(t_token_list *token)
{
	if (token->token_type != PIPE && token->token_type != WORD)
		if (!token->next || token->next->token_type != WORD)
			return (1);
	return (0);
}

//se fizermos o bonus os check AND OR e check SUBSHELL serao adicionados
//e tambem seria removido o check_consecutive_operators errors como e obv :'(
int	check_syntax_errors(t_token_list *list)
{
	t_token_list	*prev;

	if (!list)
		return (0);
	prev = NULL;
	while (list)
	{
		if (check_pipe_syntax_errors(list, prev))
		{
			put_token_syntax_error(list);
			return (1);
		}
		else if (check_redir_syntax_errors(list))
		{
			put_token_syntax_error(list);
			return (1);
		}
		prev = list;
		list = list->next;
	}
	return (0);
}
