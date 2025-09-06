/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:25:45 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/06 00:27:12 by bpires-r         ###   ########.fr       */
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

static char	*strip_quotes(char *content)
{
	int		i;
	int		k;
	char	quote;
	char	*res;

	if (!content)
		return (NULL);
	res = malloc(ft_strlen(content) + 1);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	quote = 0;
	while (content[i])
	{
		if (!quote && (content[i] == '\'' || content[i] == '"'))
			quote = content[i];
		else if (quote && content[i] == quote)
			quote = 0;
		else
			res[k++] = content[i];
		i++;
	}
	res[k] = '\0';
	return (res);
}

static void	lex_word_node(char *line, int *i, int *start, t_token_list *node)
{
	char			quote;
	char			*raw;

	while (line[*i] && !is_space(line[*i]) && line[*i] != '|'
		&& line[*i] != '>' && line[*i] != '<'
		&& line[*i] != '(' && line[*i] != ')')
	{
		if (set_quote_type(line, *i))
		{
			quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	raw = ft_substr(line, *start, *i - *start);
	node->quote_type = detect_quote_type(raw);
	node->content = strip_quotes(raw);
	free(raw);
}

t_token_list	*lex_node(char *line, int *i)
{
	int				start;
	t_token_list	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->next = NULL;
	node->content = NULL;
	start = *i;
	set_type(node, line, i);
	node->subshell_level = 0;
	if (node->token_type != WORD)
		add_content(node, i);
	else
		lex_word_node(line, i, &start, node);
	return (node);
}
