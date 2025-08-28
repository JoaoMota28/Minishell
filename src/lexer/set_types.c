/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:08:47 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/27 22:14:48 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_type(t_token_list *node, char *line, int *i)
{
	if (line[*i] == '|' && line[*i + 1] == '|')
	{
		node->token_type = OR;
		*i += 2;
	}
	else if (line[*i] == '&' && line[*i + 1] == '&')
	{
		node->token_type = AND;
		*i += 2;
	}
	else if (line[*i] == '|')
	{
		node->token_type = PIPE;
		(*i)++;
	}
	else if (line[*i] == '(')
	{
		node->token_type = SUBSHELL;
		node->p_type = P_OPEN;
		node->subshell_level++;
		(*i)++;
	}
	else if (line[*i] == ')')
	{
		node->token_type = SUBSHELL;
		node->p_type = P_CLOSED;
		node->subshell_level--;
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		node->token_type = AP_R_OUT;
		*i += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		node->token_type = HERE_DOC;
		*i += 2;
	}
	else if (line[*i] == '<')
	{
		node->token_type = R_IN;
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		node->token_type = R_OUT;
		(*i)++;
	}
	else
		node->token_type = WORD;
}


t_quote_type	set_quote_type(char *line, int index)
{
	if (line[index] == '\'')
		return (SINGLE_O);
	else if (line[index] == '"')
		return (DOUBLE_O);
	else
		return (UNQUOTED);
}

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

t_p_type	check_balance_p(char *line)
{
	int			i;
	int			balance;

	balance = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
			balance++;
		else if (line[i] == ')')
			balance--;
		i++;
	}
	if (balance)
		return (P_OPEN);
	return (P_CLOSED);
}

t_quote_type	detect_quote_type(char *word)
{
	int i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			return (SINGLE_O);
		if (word[i] == '"')
			return (DOUBLE_O);
		i++;
	}
	return (UNQUOTED);
}
