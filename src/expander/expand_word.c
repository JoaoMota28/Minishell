/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 07:20:32 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 13:12:28 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**is_wc(char **words, int w)
{
	char	*pattern;
	char	**matches;
	char	*restored;
	int		m;

	pattern = ft_strdup(words[w]);
	matches = expand_wildcard(pattern);
	if (!matches)
	{
		restored = restore_quoted_wc(pattern);
		free(words[w]);
		words[w] = restored;
		free(pattern);
		return (words);
	}
	free(words[w]);
	words[w] = ft_strdup(matches[0]);
	m = 1;
	while (matches[m])
	{
		words = str_to_array(words, ft_strdup(matches[m]));
		m++;
	}
	free_ar((void **)matches);
	return (free(pattern), words);
}

static char	**glob_words(char **words)
{
	char	*restored;
	int		w;

	if (!words)
		return (words);
	w = 0;
	while (words[w])
	{
		if (ft_strchr(words[w], '*'))
			words = is_wc(words, w);
		else
		{
			restored = restore_quoted_wc(words[w]);
			free(words[w]);
			words[w] = restored;
		}
		w++;
	}
	return (words);
}

static char	**handle_unquoted(char *s, char **words, int *arr[2])
{
	int		start;
	char	*segm;
	char	*is_marked;
	int		w;

	start = *(arr[0]);
	while (s[*(arr[0])] && s[*(arr[0])] != '\'' && s[*(arr[0])] != '"')
		(*(arr[0]))++;
	segm = ft_substr(s, start, *(arr[0]) - start);
	if (arr[1] && *arr[1])
    {
        is_marked = mark_quoted_wc(segm);
        free(segm);
        segm = is_marked;
        *arr[1] = 0;
    }
	w = last_word_i(words);
	words[w] = str_append(words[w], segm);
	free(segm);
	return (words);
}

static char	**check_rules(char *s, char **words, t_minishell *data)
{
	int	arr[2];

	arr[0] = 0;
	arr[1] = 0;
	while (s[arr[0]])
	{
		if (s[arr[0]] == '\'')
		{
			words = handle_single(s, words, &arr[2]);
			continue ;
		}
		if (s[arr[0]] == '"')
		{
			words = handle_double(s, words, data, &arr[2]);
			continue ;
		}
		if (s[arr[0]] == '$')
		{
			words = handle_dollar(s, words, data, &arr[2]);
			continue ;
		}
		words = handle_unquoted(s, words, &arr[2]);
	}
	return (words);
}

char	**expand_word(t_tree *node, char *s, t_minishell *data)
{
	char	**words;

	words = NULL;
	words = str_to_array(words, ft_strdup(""));
	node->q_type = set_quote_type(s, 0);
	words = check_rules(s, words, data);
	words = glob_words(words);
	return (words);
}
