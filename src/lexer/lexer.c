/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:37:54 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/25 19:32:27 by bpires-r         ###   ########.fr       */
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
	else
		return ;
}

static t_token_list	*lex_node(char *line, int *i)
{
	int				start;
	t_token_list	*node;
	char			quote;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->next = NULL;
	start = *i;
	set_type(node, line, i);
	node->quote_type = detect_quote_type(line);
	if (node->token_type != WORD)
		add_content(node, i);
	else
	{
		while (line[*i] && !is_space(line[*i]) && line[*i] != '|'
			&& line[*i] != '>' && line[*i] != '<')
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
		node->content = ft_substr(line, start, *i - start);
	}
	return (node);
}

int	lexer(char *line, t_minishell *data)
{
	int				i;
	t_token_list	*node;
	t_token_list	*head;
	t_quote_type	type;

	(void)data;
	i = 0;
	head = NULL;
	node = NULL;
	type = is_unquoted(line);
	if (type)
		return(/*printf("%d\n", data->exit_code), */put_unclosed_syntax_error(type), 2);
	while (line[i])
	{
		if (is_space(line[i]))
		{
			i++;
			continue ;
		}
		node = lex_node(line, &i);
		//printf("Token: [%s]\n\n", node->content);
		expander(node, data);
		if (node->token_type == WORD && !node->content)
		{
			free(node);
			continue;
		}
		ft_lstadd_back((t_list **)&head, (t_list *)node);
		//printf("%s\n -> %d\n", node->content, node->token_type);
	}
	if (check_syntax_errors(head))
		return (/*printf("%d\n", data->exit_code),*/free_tokens(head), 2);
	return (parser(data, head));
}
