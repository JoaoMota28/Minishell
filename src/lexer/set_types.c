/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:08:47 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/19 20:11:48 by bpires-r         ###   ########.fr       */
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
