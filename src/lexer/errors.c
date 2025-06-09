/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:45:01 by bpires-r          #+#    #+#             */
/*   Updated: 2025/05/29 18:06:32 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_unclosed_syntax_error(t_quote_type type)
{
	if (type == SINGLE_O)
		ft_putstr_fd(SYNTAX_ERROR_OPEN_SQUOTE, 2);
	else if (type == DOUBLE_O)
		ft_putstr_fd(SYNTAX_ERROR_OPEN_DQUOTE, 2);
}

void	put_token_syntax_error(t_token_list *token)
{
	if (token->token_type == PIPE)
		ft_putstr_fd(SYNTAX_ERROR_PIPE, 2);
	else if (token->token_type == R_IN)
		ft_putstr_fd(SYNTAX_ERROR_R_IN, 2);
	else if (token->token_type == R_OUT)
		ft_putstr_fd(SYNTAX_ERROR_R_OUT, 2);
	else if (token->token_type ==  AP_R_OUT)
		ft_putstr_fd(SYNTAX_ERROR_AP_R_OUT, 2);
	else if (token->token_type == HERE_DOC)
		ft_putstr_fd(SYNTAX_ERROR_HEREDOC, 2);
}
