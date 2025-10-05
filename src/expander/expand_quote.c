/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:16:35 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/05 10:38:26 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_len(char *s, int quoted, t_minishell *data)
{
	if (quoted == '\'')
		return (ft_strlen(s));
	return (get_expanded_len(s, data));
}

int	handle_quoted_dollar(char *raw, int *i, t_minishell *data, char *out, int *k)
{
	int j;
	int	q;
	char *seg;

	q = raw[*i + 1];
	j = *i + 2;
	while (raw[j] && raw[j] != q)
		j++;
	seg = ft_substr(raw, *i + 2, j - (*i + 2));
	if (!seg)
		return (-1);
	if (out)
		*k += handle_copy(seg, q, data, out + *k);
	else
		*k += handle_len(seg, q, data);
	free(seg);
	if (raw[j] && q)
		*i = j + 1;
	else
		*i = j;
	return (0);
}

int	handle_normal_segm(char *raw, int *i, t_minishell *data, char *out, int *k)
{
	int j;
	int q = 0;
	char *seg;

	handle_quoted(&q, &j, i, raw);
	seg = ft_substr(raw, *i, j - *i);
	if (!seg)
		return (-1);
	if (out)
		*k += handle_copy(seg, q, data, out + *k);
	else
		*k += handle_len(seg, q, data);
	free(seg);
	update_index(i, &j, raw, &q);
	return (0);
}

int	handle_copy(char *s, int quoted, t_minishell *data, char *dest)
{
	char	*tmp;
	int		len;

	if (quoted == '\'')
	{
		len = ft_strlen(s);
		ft_memcpy(dest, s, len);
		return (len);
	}
	tmp = expand_nodes(s, data);
	if (!tmp)
		tmp = ft_strdup("");
	len = ft_strlen(tmp);
	ft_memcpy(dest, tmp, len);
	free(tmp);
	return (len);
}

void	handle_quoted(int *q, int *j, int *i, char *raw)
{
	if (raw[*i] == '\'' || raw[*i] == '"')
	{
		*q = raw[*i];
		(*i)++;
	}
	*j = *i;
	if (*q)
		while (raw[*j] && raw[*j] != *q)
			(*j)++;
	else
	{
		while (raw[*j] && raw[*j] != '\'' && raw[*j] != '"')
			(*j)++;
		if (raw[*j] && *j > *i && raw[*j - 1] == '$')
			(*j)--;
	}
}

