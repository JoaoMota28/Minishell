/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:37:54 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/04 00:36:22 by jomanuel         ###   ########.fr       */
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

static t_token_list	*lex_node(char *line, int *i)
{
	int				start;
	t_token_list	*node;
	char			quote;
	char			*raw;

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
	{
		while (line[*i] && !is_space(line[*i]) && line[*i] != '|'
			&& line[*i] != '>' && line[*i] != '<' && line[*i] != '(' && line[*i] != ')')
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
		raw = ft_substr(line, start, *i - start);
		node->quote_type = detect_quote_type(raw);
		node->content = strip_quotes(raw);
		free(raw);
	}
	return (node);
}

static void	assign_subshell(t_token_list *node, int *current_level)
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

int	lexer(char *line, t_minishell *data)
{
	int				i;
	int				current_level;
	t_token_list	*node;
	t_token_list	*head;
	t_quote_type	type;
	t_p_type		parentheses;

	(void)data;
	i = 0;
	head = NULL;
	node = NULL;
	type = is_unquoted(line);
	parentheses = check_balance_p(line);
	current_level = 0;
	if (type)
		return(put_unclosed_syntax_error(type, parentheses), 2);
	if (parentheses)
		return (put_unclosed_syntax_error(type, parentheses), 2);
	while (line[i])
	{
		if (is_space(line[i]))
		{
			i++;
			continue ;
		}
		node = lex_node(line, &i);
		assign_subshell(node, &current_level);
		if (node->token_type == WORD && (!node->content || !*node->content))
		{
			if (node->content)
				free(node->content);
			free(node);
			continue;
		}
		ft_lstadd_back((t_list **)&head, (t_list *)node);
		//printf("Token Content -> %s\n", node->content);
	}
	if (check_syntax_errors(head))
		return (free_tokens(head), 2);
//	if (node)
//	{
//		free(node->content);
//		free(node);
//	}
	return (parser(data, head));
}
