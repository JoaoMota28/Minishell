/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:59:39 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/05 16:30:30 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_p_closed(t_token_list *token, t_token_list *prev)
{
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

static int	check_p_open(t_token_list *token, t_token_list *prev)
{
	if (!ft_strcmp(token->content, "("))
	{
		if (token->next && token->next->token_type == SUBSHELL
			&& !ft_strcmp(token->next->content, ")"))
			return (1);
		if (prev && prev->token_type == WORD)
			return (1);
		if (prev && (prev->token_type == R_IN || prev->token_type == R_OUT
				|| prev->token_type == AP_R_OUT
				|| prev->token_type == HERE_DOC
				|| prev->token_type == SUBSHELL))
			return (1);
		if (token->next && (token->next->token_type == AND
				|| token->next->token_type == OR
				|| token->next->token_type == PIPE))
			return (1);
	}
	return (0);
}

int	check_subshell_syntax_errors(t_token_list *token, t_token_list *prev)
{
	if (token->token_type != SUBSHELL)
		return (0);
	if (!ft_strcmp(token->content, "("))
		if (check_p_open(token, prev))
			return (1);
	if (!ft_strcmp(token->content, ")"))
		if (check_p_closed(token, prev))
			return (1);
	return (0);
}
