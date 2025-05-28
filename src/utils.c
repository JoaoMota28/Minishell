/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:57:48 by bpires-r          #+#    #+#             */
/*   Updated: 2025/05/22 20:27:50 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

int	is_operator(t_token_type type)
{
	return (type == PIPE || type == R_IN || type == R_OUT
		|| type == AP_R_OUT || type == HERE_DOC);
}

//por agora skipa quotes mas pode skipar ()
// int	skip_closed(char *line, char c)
// {

// }