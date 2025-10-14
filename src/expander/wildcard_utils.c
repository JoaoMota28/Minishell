/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 03:12:52 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/14 19:42:33 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mark_quoted_wc(const char *s)
{
	char	*res;
	int		i;
	char	tmp[2];

	if (!s)
		return (ft_strdup(""));
	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
			tmp[0] = QUOTED_WC;
		else
			tmp[0] = s[i];
		tmp[1] = '\0';
		res = str_append(res, tmp);
		i++;
	}
	return (res);
}

char	*restore_quoted_wc(const char *s)
{
	char	*res;
	int		i;
	char	tmp[2];

	if (!s)
		return (ft_strdup(""));
	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == QUOTED_WC)
			tmp[0] = '*';
		else
			tmp[0] = s[i];
		tmp[1] = '\0';
		res = str_append(res, tmp);
		i++;
	}
	return (res);
}
