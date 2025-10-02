/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:25:45 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/02 13:49:20 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_content(t_token_list *node, int *i)
{
	(void)i;
	if (node->token_type == PIPE)
		node->content = "|";
	else if (node->token_type == R_IN)
		node->content = "<";
	else if (node->token_type == R_OUT)
		node->content = ">";
	else if (node->token_type == AP_R_OUT)
		node->content = ">>";
	else if (node->token_type == HERE_DOC)
		node->content = "<<";
	else if (node->token_type == AND)
		node->content = "&&";
	else if (node->token_type == OR)
		node->content = "||";
	else if (node->token_type == SUBSHELL && node->p_type == P_OPEN)
		node->content = "(";
	else if (node->token_type == SUBSHELL && node->p_type == P_CLOSED)
		node->content = ")";
	else
		return ;
}

static void	get_word_start(char *line, int *j)
{
	int	q;

	q = 0;
	while (line[*j])
	{
		if (!q && (is_space(line[*j]) || line[*j] == '|' || line[*j] == '>'
				|| line[*j] == '<' || line[*j] == '(' || line[*j] == ')'))
			break ;
		if (!q && (line[*j] == '\'' || line[*j] == '"'))
		{
			q = line[*j];
			(*j)++;
		}
		else if (q && line[*j] == q)
		{
			q = 0;
			(*j)++;
		}
		else
			(*j)++;
	}
}

static void	lex_word_node(char *line, int *i, t_token_list *node)
{
	int				j;

	j = *i;
	get_word_start(line, &j);
	if (j > *i)
	{
		if (node->content)
			free(node->content);
		node->content = ft_substr(line, *i, j - *i);
		node->quote_type = detect_quote_type(node->content);
	}
	if (j == *i)
		j++;
	*i = j;
}

t_token_list	*lex_node(char *line, int *i)
{
	t_token_list	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->content = NULL;
	node->p_type = P_CLOSED;
	node->quote_type = UNQUOTED;
	node->token_type = WORD;
	node->subshell_level = 0;
	set_type(node, line, i);
	if (node->token_type != WORD)
		add_content(node, i);
	else
		lex_word_node(line, i, node);
	return (node);
}
