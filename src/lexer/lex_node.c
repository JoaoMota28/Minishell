/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:25:45 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/01 00:51:11 by bpires-r         ###   ########.fr       */
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
/*
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

static void	fill_node_segment(t_token_list *node, char *line, int start, int end, t_quote_type q_type)
{
	char	*raw;

	if (end <= start)
		return ;
	raw = ft_substr(line, start, end - start);
	if (!raw)
		return ;
	if (node->content)
		free(node->content);
	node->content = ft_strdup(raw);
	node->quote_type = q_type;
	free(raw);
}

static void	handle_quote_segment(char *line, int *i, int *j, t_token_list **tmp)
{
	int				start;
	char			quote;
	t_quote_type	q_type;
	t_token_list	*new;

	quote = line[*j];
	(*j)++;
	start = *j;
	while (line[*j] && line[*j] != quote)
		(*j)++;
	if (quote == '\'')
		q_type = SINGLE_O;
	else
		q_type = DOUBLE_O;
	fill_node_segment(*tmp, line, start, *j, q_type);
	if (line[*j] == quote)
		(*j)++;
	*i = *j;
	if (line[*i] && !is_space(line[*i]) && line[*i] != '|'
		&& line[*i] != '>' && line[*i] != '<'
		&& line[*i] != '(' && line[*i] != ')')
	{
		new =  ft_calloc(1, sizeof(*new));
		if (!new)
			return ;
		new->next = NULL;
		new->content = NULL;
		new->subshell_level = 0;
		new->token_type = WORD;
		new->quote_type = UNQUOTED;
		(*tmp)->next = new;
		*tmp = new;
	}
}*/

static void	lex_word_node(char *line, int *i, int *start, t_token_list *node)
{
	int				j;
	int				q;

	q = 0;
	j = *i;
	(void)start;
	while (line[j])
	{
		if (!q && (is_space(line[j]) || line[j] == '|' || line[j] == '>'
			|| line[j] == '<' || line[j] == '(' || line[j] == ')'))
			break;
		if (!q && (line[j] == '\'' || line[j] == '"')){
			q = line[j];
			j++;
		}
		else if (q && line[j] == q)
		{
			q = 0;
			j++;
		}
		else
			j++;
	}
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
	int				start;
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
	start = *i;
	set_type(node, line, i);
	if (node->token_type != WORD)
		add_content(node, i);
	else
		lex_word_node(line, i, &start, node);
	return (node);
}
