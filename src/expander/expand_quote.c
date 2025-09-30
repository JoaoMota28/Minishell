/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:16:35 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/27 21:56:59 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  handle_len(char *s, int quoted, t_minishell *data)
{
    if (quoted == '\'')
        return (ft_strlen(s));
    return (get_expanded_len(s, data));
}

static int  handle_copy(char *s, int quoted, t_minishell *data, char *dest)
{
    char    *tmp;
    int     len;

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

static int	expand_segment(char *raw, t_minishell *data, char *out)
{
	int		i;
	int		j;
	int		q;
	int		k;
	char	*seg;

	i = 0;
	k = 0;
	while (raw[i])
	{
		q = 0;
		if (raw[i] == '\'' || raw[i] == '"')
		{
			q = raw[i];
			i++;
		}
		j = i;
		if (q)
			while (raw[j] && raw[j] != q)
				j++;
		else
			while (raw[j] && raw[j] != '\'' && raw[j] != '"')
				j++;
		seg = ft_substr (raw, i, j - i);
		if (!seg)
			return (-1);
		if (out)
			k += handle_copy(seg, q, data, out + k);
		else
			k += handle_len(seg, q, data);
		free(seg);
		if (q && raw[j])
			i = j + 1;
		else
			i = j;
	}
	if (out)
		out[k] = '\0';
	return (k);
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