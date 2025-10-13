/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:33:47 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/13 07:27:17 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	i;

	i = 0;
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

void	assign_subshell(t_token_list *node, int *current_level)
{
	if (node->token_type == SUBSHELL && node->p_type == P_OPEN)
	{
		node->subshell_level = *current_level;
		(*current_level)++;
	}
	else if (node->token_type == SUBSHELL && node->p_type == P_CLOSED)
	{
		(*current_level)--;
		node->subshell_level = *current_level;
	}
	else
	{
		node->subshell_level = *current_level;
		if (*current_level > 0)
			node->p_type = P_OPEN;
		else
			node->p_type = P_CLOSED;
	}
}
