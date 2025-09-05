/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:08:47 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/05 01:47:50 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pipe_token(t_token_list *node, char *line, int *i)
{
	if (line[*i] == '|')
	{
		node->token_type = PIPE;
		(*i)++;
	}
}

static void	init_and_or_token(t_token_list *node, char *line, int *i)
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
}

static void	init_redir_token(t_token_list *node, char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
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
}

static void	init_subshell_token(t_token_list *node, char *line, int *i)
{
	if (line[*i] == '(')
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
}

void	set_type(t_token_list *node, char *line, int *i)
{
	if (line[*i] == '|' && line[*i + 1] == '|')
		init_and_or_token(node, line, i);
	else if (line[*i] == '&' && line[*i + 1] == '&')
		init_and_or_token(node, line, i);
	else if (line[*i] == '|')
		init_pipe_token(node, line, i);
	else if (line[*i] == '(')
		init_subshell_token(node, line, i);
	else if (line[*i] == ')')
		init_subshell_token(node, line, i);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		init_redir_token(node, line, i);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		init_redir_token(node, line, i);
	else if (line[*i] == '<')
		init_redir_token(node, line, i);
	else if (line[*i] == '>')
		init_redir_token(node, line, i);
	else
		node->token_type = WORD;
}
