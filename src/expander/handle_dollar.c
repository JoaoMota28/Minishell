/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:24:14 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 13:25:05 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_double_char(char *o, const char *s, int *j)
{
	char	tmp[2];

	if (s[*j] == '*')
		tmp[0] = QUOTED_WC;
	else
		tmp[0] = s[*j];
	tmp[1] = '\0';
	o = str_append(o, tmp);
	(*j)++;
	return (o);
}

char	*handle_double_dollar(char *o, char *p, t_minishell *d, int *c)
{
	char	*tmp;
	char	*marked;

	tmp = expand_dollar(p, c, d);
	if (tmp)
	{
		marked = mark_quoted_wc(tmp);
		o = str_append(o, marked);
		free(tmp);
		free(marked);
	}
	return (o);
}
