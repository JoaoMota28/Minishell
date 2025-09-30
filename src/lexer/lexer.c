/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:37:54 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/30 02:33:49 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lex_empty_node(t_token_list *node)
{
	if (node->token_type == WORD && (!node->content || !*node->content))
	{
		if (node->content)
			free(node->content);
		node->content = ft_strdup("");
	}
}

int	lexer(char *line, t_minishell *data)
{
	int				i;
	int				current_level;
	t_token_list	*node;
	t_token_list	*head;

	i = 0;
	head = NULL;
	node = NULL;
	current_level = 0;
	if (check_unclosed(line))
		return (2);
	while (line[i])
	{
		if (is_space(line[i++]))
			continue ;
		i--;
		node = lex_node(line, &i);
		assign_subshell(node, &current_level);
		lex_empty_node(node);
		ft_lstadd_back((t_list **)&head, (t_list *)node);
	}
	if (check_syntax_errors(head))
		return (free_tokens(head), 2);
	return (parser(data, head));
}
