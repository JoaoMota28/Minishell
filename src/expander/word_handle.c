/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 08:37:59 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/14 19:36:56 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_double(char *s, int *i, t_minishell *data)
{
	char	*out;
	char	*tmp;
	int		j;
	int		len;
	char	*marked;
	char	tmpwc[2];

	j = *i + 1;
	out = ft_strdup("");
	while (s[j] && s[j] != '"')
	{
		if (s[j] == '$')
		{
			tmp = expand_dollar(&s[j], &len, data);
			if (tmp)
			{
				marked = mark_quoted_wc(tmp);
				out = str_append(out, marked);
				free(tmp);
				free(marked);
			}
			j += len;
		}
		else
		{
			if (s[j] == '*')
				tmpwc[0] = QUOTED_WC;
			else
				tmpwc[0] = s[j];
			tmpwc[1] = '\0';
			out = str_append(out, tmpwc);
			j++;
		}
	}
	*i = j;
	return (out);
}

static char	*expand_var(char *s, int *i, t_minishell *data)
{
	int		len;
	char	*res;

	res = expand_dollar(&s[*i], &len, data);
	*i += len;
	return (res);
}

char	**handle_single(const char *s, int *i, char **words)
{
	int		start;
	char	*tmp;
	char	*marked;
	int		w;

	start = *i + 1;
	*i = start;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	tmp = ft_substr(s, start, *i - start);
	marked = mark_quoted_wc(tmp);
	free(tmp);
	w = last_word_i(words);
	words[w] = str_append(words[w], marked);
	free(marked);
	if (s[*i] == '\'')
		(*i)++;
	return (words);
}

char	**handle_double(char *s, int *i, char **words, t_minishell *data)
{
	char	*tmp;
	int		w;

	tmp = expand_double(s, i, data);
	w = last_word_i(words);
	words[w] = str_append(words[w], tmp);
	free(tmp);
	if (s[*i] == '"')
		(*i)++;
	return (words);
}

char	**handle_dollar(char *s, int *i, char **words, t_minishell *data)
{
	char	*tmp;
	char	**splitted;
	int		w;
	int		m;

	tmp = expand_var(s, i, data);
	w = last_word_i(words);
	if (!tmp)
		return (words);
	if (!ft_strchr(tmp, ' '))
	{
		words[w] = str_append(words[w], tmp);
		free(tmp);
		return (words);
	}
	splitted = ft_split(tmp, ' ');
	free(tmp);
	if (!splitted)
		return (words);
	words[w] = str_append(words[w], splitted[0]);
	m = 1;
	while (splitted[m])
		words = str_to_array(words, ft_strdup(splitted[m++]));
	free_ar((void **)splitted);
	return (words);
}
