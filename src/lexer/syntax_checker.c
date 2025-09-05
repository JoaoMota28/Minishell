/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:56:20 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/05 16:29:05 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc_syntax_errors(t_token_list *token)
{
	if (token->token_type == HERE_DOC)
		if (!token->next || token->next->token_type != WORD)
			return (1);
	return (0);
}

int	check_and_or_syntax_errors(t_token_list *token, t_token_list *prev)
{
	if (token->token_type == AND || token->token_type == OR)
	{
		if (!prev || !token->next)
			return (1);
		if (token->next->token_type != WORD
			&& token->next->token_type != R_IN
			&& token->next->token_type != R_OUT
			&& token->next->token_type != AP_R_OUT
			&& token->next->token_type != HERE_DOC
			&& token->next->token_type != SUBSHELL)
			return (1);
	}
	return (0);
}

int	check_pipe_syntax_errors(t_token_list *token, t_token_list *prev)
{
	if (token->token_type == PIPE)
		if (!prev || !token->next
			|| token->next->token_type == PIPE)
			return (1);
	return (0);
}

int	check_redir_syntax_errors(t_token_list *token)
{
	if (token->token_type != PIPE && token->token_type != WORD
		&& token->token_type != AND && token->token_type != OR
		&& token->token_type != SUBSHELL && token->token_type != HERE_DOC)
		if (!token->next || token->next->token_type != WORD)
			return (1);
	return (0);
}

int	check_syntax_errors(t_token_list *list)
{
	t_token_list	*prev;

	prev = NULL;
	while (list)
	{
		if (check_and_or_syntax_errors(list, prev))
		{
			if (list->next && list->next->token_type == PIPE)
				return (put_token_syntax_error(list->next), 1);
			else
				return (put_token_syntax_error(list), 1);
		}
		else if (check_pipe_syntax_errors(list, prev))
			return (put_token_syntax_error(list), 1);
		else if (check_subshell_syntax_errors(list, prev))
			return (put_token_syntax_error(list), 1);
		else if (check_heredoc_syntax_errors(list))
			return (put_token_syntax_error(list), 1);
		else if (check_redir_syntax_errors(list))
			return (put_token_syntax_error(list), 1);
		prev = list;
		list = list->next;
	}
	return (0);
}
