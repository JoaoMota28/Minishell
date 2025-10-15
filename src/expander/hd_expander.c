/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 08:43:26 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 11:31:42 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dollar_expansion(char *o, char *p, t_minishell *d, int *c)
{
	char	*val;

	val = expand_dollar(p, c, d);
	if (val)
	{
		o = str_append(o, val);
		free(val);
	}
	if (*c <= 0)
		*c = 1;
	return (o);
}

static char	*expand_heredoc_line(char *line, t_minishell *data)
{
	char	*out;
	char	*seg;
	int		i;
	int		consumed;

	if (!line)
		return (ft_strdup(""));
	out = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			out = handle_dollar_expansion(out, &line[i], data, &consumed);
			i += consumed;
		}
		else
		{
			seg = ft_substr(line, i, 1);
			out = str_append(out, seg);
			free(seg);
			i++;
		}
	}
	return (out);
}

char	*expand_heredoc(char *line, t_tree *delim, t_minishell *data)
{
	char	*expanded;

	if (detect_quote_type(delim->content))
		return (ft_strdup(line));
	expanded = expand_heredoc_line(line, data);
	if (!expanded)
		return (ft_strdup(""));
	return (expanded);
}
