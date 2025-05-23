/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:37:54 by bpires-r          #+#    #+#             */
/*   Updated: 2025/05/23 20:10:52 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_type(t_token_list *node, char *line, int *i)
{
	if (line[*i] == '|')
	node->token_type = PIPE;
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
	printf("TYPE: %i\n", node->token_type);
}

static void    add_content(t_token_list *node, int *i)
{
    if (node->token_type == PIPE)
	{
		node->content = "|";
		(*i)++;
	}
	else if (node->token_type == R_IN)
		node->content = "<";
	else if (node->token_type == R_OUT)
		node->content = ">";
	else if (node->token_type == AP_R_OUT)
		node->content = ">>";
	else if (node->token_type == HERE_DOC)
		node->content = "<<";
	else
		return ;
}


t_token_list *lexer(char *line)
{
	t_token_list	*node;
	t_token_list	*head;
	int	i;
	int start;

	i = 0;
	head = NULL;
	node = NULL;
	while (line[i])
	{
		if (is_space(line[i]))
		{
			i++;
			continue ;
		}
		node = malloc(sizeof(*node));
		if (!node)
			return (NULL);
		node->next = NULL;
		start = i;
		set_type(node, line, &i);
		if (node->token_type != WORD)
			add_content(node, &i);
		else
		{
			while (line[i] && !is_space(line[i]) && line[i] != '|'
				&& line[i] != '>' && line[i] != '<')
					i++;
			node->content = ft_substr(line, start, i - start);
		}
		ft_lstadd_back((t_list **)&head, (t_list *)node);
	}
	//vai returnar parser :D
	return (head);
}
