/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:16:35 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/08 13:47:00 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quoted_dollar(char *raw, t_minishell *data, char *out, int (*ind)[2])
{
	int		j;
	int		q;
	char	*seg;

	q = raw[(*ind)[0] + 1];
	j = (*ind)[0] + 2;
	while (raw[j] && raw[j] != q)
		j++;
	seg = ft_substr(raw, (*ind)[0] + 2, j - ((*ind)[0] + 2));
	if (!seg)
		return (-1);
	if (out)
		(*ind)[1] += handle_copy(seg, q, data, out + (*ind)[1]);
	else
		(*ind)[1] += handle_len(seg, q, data);
	free(seg);
	if (raw[j] && q)
		(*ind)[0] = j + 1;
	else
		(*ind)[0] = j;
	return (0);
}

int	handle_normal_segm(char *raw, t_minishell *data, char *out, int (*ind)[2])
{
	int		j;
	int		q;
	char	*seg;

	q = 0;
	handle_quoted(&q, &j, ind[0], raw);
	seg = ft_substr(raw, (*ind)[0], j - (*ind)[0]);
	if (!seg)
		return (-1);
	if (out)
		(*ind)[1] += handle_copy(seg, q, data, out + (*ind)[1]);
	else
		(*ind)[1] += handle_len(seg, q, data);
	free(seg);
	update_index(ind[0], &j, raw, &q);
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

char	*expand_quote(char *raw, t_minishell *data)
{
	int		len;
	char	*res;

	if (!raw)
		return (NULL);
	len = expand_segment(raw, data, NULL);
	if (len < 0)
		return (NULL);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	expand_segment(raw, data, res);
	return (res);
}
