/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:56:20 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/28 22:47:06 by bpires-r         ###   ########.fr       */
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

int	check_subshell_syntax_errors(t_token_list *token, t_token_list *prev)
{
	printf("token: %s\n", token->content);
	if (token->token_type != SUBSHELL)
		return (0);
	if (!ft_strcmp(token->content, "("))
	{
		if (token->next && token->next->token_type == SUBSHELL
			&& !ft_strcmp(token->content, ")"))
			return (1);
		if (prev && prev->token_type == WORD)
			return (1);
		if (prev && (prev->token_type == R_IN || prev->token_type == R_OUT
			|| prev->token_type == AP_R_OUT || prev->token_type == HERE_DOC))
			return (1);
		if (token->next && (token->next->token_type == AND
			|| token->next->token_type == OR
			|| token->next->token_type == PIPE))
			return (1);
	}
	if (!ft_strcmp(token->content, ")"))
	{
		if (prev && (prev->token_type == AND
			|| prev->token_type == OR
			|| prev->token_type == PIPE))
			return (1);
		if (token->next && token->next->token_type == WORD)
			return (1);
	}
	return (0);
}

//se fizermos o bonus os check AND OR e check SUBSHELL serao adicionados
//e tambem seria removido o check_consecutive_operators errors como e obv :'(
int	check_syntax_errors(t_token_list *list)
{
	t_token_list	*prev;

	if (!list)
		return (0);
	prev = NULL;
	while (list)
	{
		if (check_and_or_syntax_errors(list, prev))
		{
			if (list->next && list->next->token_type == PIPE)
				put_token_syntax_error(list->next);
			else
				put_token_syntax_error(list);
			return (1);
		}
		else if (check_pipe_syntax_errors(list, prev))
		{
			put_token_syntax_error(list);
			return (1);
		}
		else if (check_subshell_syntax_errors(list, prev))
		{
			put_token_syntax_error(list);
			return (1);
		}
		else if (check_heredoc_syntax_errors(list))
		{
			put_token_syntax_error(list);
			return (1);
		}
		else if (check_redir_syntax_errors(list))
		{
			put_token_syntax_error(list);
			return (1);
		}
		prev = list;
		list = list->next;
	}
	return (0);
}
