/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 07:20:32 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 19:13:28 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	**handle_rules(char **words, int *arr[2], char *s, t_minishell *data)
{
	while (s[*(arr[0])])
	{
		if (s[*(arr[0])] == '\'')
		{
			words = handle_single(s, words, arr);
			continue ;
		}
		if (s[*(arr[0])] == '"')
		{
			words = handle_double(s, words, data, arr);
			continue ;
		}
		if (s[*(arr[0])] == '$')
		{
			words = handle_dollar(s, words, data, arr);
			continue ;
		}
		words = handle_unquoted(s, words, arr);
	}
	return (words);
}

static char	**check_rules(char *s, char **words, t_minishell *data)
{
	int	*arr[2];
	int	idx;
	int	marked;

	idx = 0;
	marked = 0;
	arr[0] = &idx;
	arr[1] = &marked;
	words = handle_rules(words, arr, s, data);
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
