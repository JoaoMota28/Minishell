/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:56:20 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/05 02:01:34 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
