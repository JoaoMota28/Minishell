/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_memory_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 17:49:18 by bpires-r          #+#    #+#             */
/*   Updated: 2025-05-28 17:49:18 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token_list *list)
{
	t_token_list    *tmp;

	while (list)
	{
		tmp = list->next;
		if (list->content && list->token_type == WORD)
			free(list->content);
		free(list);
		list = tmp;
	}
}
