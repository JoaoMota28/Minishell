/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:45:01 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/05 01:31:54 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_unclosed_syntax_error(t_quote_type type, t_p_type paretheses)
{
	if (type == SINGLE_O)
		ft_putstr_fd(SYNTAX_ERROR_OPEN_SQUOTE, 2);
	else if (type == DOUBLE_O)
		ft_putstr_fd(SYNTAX_ERROR_OPEN_DQUOTE, 2);
	else if (paretheses == P_OPEN)
		ft_putstr_fd(SYNTAX_ERROR_OPEN_P, 2);
}

void	put_token_syntax_error(t_token_list *token)
{
	if (token->token_type == AND)
		ft_putstr_fd(SYNTAX_ERROR_AND, 2);
	else if (token->token_type == OR)
		ft_putstr_fd(SYNTAX_ERROR_OR, 2);
	else if (token->token_type == SUBSHELL && token->p_type == P_OPEN)
	{
		ft_putstr_fd(SYNTAX_ERROR_P_OPEN, 2);
	}
	else if (token->token_type == SUBSHELL && token->p_type == P_CLOSED)
		ft_putstr_fd(SYNTAX_ERROR_P_CLOSED, 2);
	else if (token->token_type == PIPE)
		ft_putstr_fd(SYNTAX_ERROR_PIPE, 2);
	else if (token->token_type == AP_R_OUT)
		ft_putstr_fd(SYNTAX_ERROR_AP_R_OUT, 2);
	else if (token->token_type == HERE_DOC)
		ft_putstr_fd(SYNTAX_ERROR_HEREDOC, 2);
	else if (token->token_type == R_IN)
		ft_putstr_fd(SYNTAX_ERROR_R_IN, 2);
	else if (token->token_type == R_OUT)
		ft_putstr_fd(SYNTAX_ERROR_R_OUT, 2);
}

void	free_tokens(t_token_list *list)
{
	t_token_list	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->content && list->token_type == WORD)
			free(list->content);
		if (list)
			free(list);
		list = tmp;
	}
}
