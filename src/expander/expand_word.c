/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 07:20:32 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/13 08:36:32 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**append_matched(char **words, char **matched)
{
	int	m;
	int	w;

	m = 0;
	while (matched && matched[m])
	{
		w = last_word_i(words);
		if (m == 0)
			words[w] = str_append(words[w], matched[m]);
		else
			words = str_to_array(words, ft_strdup(matched[m]));
		m++;
	}
	return (words);
}

static char	**handle_wildc_seg(char *seg, char **words)
{
	char	**matched;

	matched = expand_unq_wildcard(seg);
	words = append_matched(words, matched);
	if (matched)
		free_ar((void **)matched);
	free(seg);
	return (words);
}

static char	**handle_unquoted(char *s, int *i, char **words)
{
	int		start;
	char	*segm;
	int		w;

	start = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	segm = ft_substr(s, start, *i - start);
	if (ft_strchr(segm, '*'))
		return (handle_wildc_seg(segm, words));
	w = last_word_i(words);
	words[w] = str_append(words[w], segm);
	free(segm);
	return (words);
}

static char	**check_rules(char *s, char **words, t_minishell *data)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			words = handle_single(s, &i, words);
			continue ;
		}
		if (s[i] == '"')
		{
			words = handle_double(s, &i, words, data);
			continue ;
		}
		if (s[i] == '$')
		{
			words = handle_dollar(s, &i, words, data);
			continue ;
		}
		words = handle_unquoted(s, &i, words);
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
	return (words);
}
