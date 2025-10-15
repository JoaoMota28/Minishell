/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 08:37:59 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 13:03:50 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_double_dollar(char *o, char *p, t_minishell *d, int *c)
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

static char	*expand_double(char *s, int *i, t_minishell *data)
{
	char	*out;
	int		j;
	int		len;
	char	tmp[2];

	j = *i + 1;
	out = ft_strdup("");
	while (s[j] && s[j] != '"')
	{
		if (s[j] == '$' && s[j + 1] == '"')
		{
			out = handle_double_dollar(out, &s[j], data, &len);
			j += len;
		}
		else
		{
			if (s[j] == '*')
				tmp[0] = QUOTED_WC;
			else
				tmp[0] = s[j];
			tmp[1] = '\0';
			out = str_append(out, tmp);
			j++;
		}
	}
	return (*i = j, out);
}

static char	*expand_var(char *s, int *i, t_minishell *data)
{
	int		len;
	char	*res;

	res = expand_dollar(&s[*i], &len, data);
	*i += len;
	return (res);
}

char	**handle_single(const char *s, char **words, int *arr[2])
{
	int		start;
	char	*tmp;
	char	*marked;
	int		w;

	start = *(arr[0]) + 1;
	*(arr[0]) = start;
	while (s[*(arr[0])] && s[*(arr[0])] != '\'')
		(*(arr[0]))++;
	tmp = ft_substr(s, start, *(arr[0]) - start);
	marked = mark_quoted_wc(tmp);
	free(tmp);
	w = last_word_i(words);
	words[w] = str_append(words[w], marked);
	free(marked);
	if (s[*(arr[0])] == '\'')
		(*(arr[0]))++;
	*arr[1] = 0;
	return (words);
}

char	**handle_double(char *s, char **words, t_minishell *data, int *arr[2])
{
	char	*tmp;
	int		w;

	tmp = expand_double(s, arr[0], data);
	w = last_word_i(words);
	words[w] = str_append(words[w], tmp);
	free(tmp);
	if (s[*(arr[0])] == '"')
		(*(arr[0]))++;
	*(arr[1]) = 0;
	return (words);
}

char	**handle_dollar(char *s, char **words, t_minishell *data, int *arr[2])
{
	char	*tmp;
	char	**splitted;
	int		w;
	int		m;

	tmp = expand_var(s, arr[0], data);
	w = last_word_i(words);
	if (!tmp)
		return (*(arr[1]) = 0, words);
	if (!ft_strchr(tmp, ' '))
	{
		words[w] = str_append(words[w], tmp);
		free(tmp);
		*(arr[1]) = 1;
		return (words);
	}
	splitted = ft_split(tmp, ' ');
	free(tmp);
	if (!splitted)
		return (*(arr[1]) = 0, words);
	words[w] = str_append(words[w], splitted[0]);
	m = 1;
	while (splitted[m])
		words = str_to_array(words, ft_strdup(splitted[m++]));
	free_ar((void **)splitted);
	*(arr[1]) = 1;
	return (words);
}
