/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 07:20:32 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 09:54:47 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**glob_words(char **words)
{
	char	*pattern;
	char	**matches;
	char	*restored;
	int		w;
	int		m;

	if (!words)
		return (words);
	w = 0;
	while (words[w])
	{
		if (ft_strchr(words[w], '*'))
		{
			pattern = ft_strdup(words[w]);
			matches = expand_wildcard(pattern);
			if (!matches)
			{
				restored = restore_quoted_wc(pattern);
				free(words[w]);
				words[w] = restored;
				free(pattern);
			}
			else
			{
				free(words[w]);
				words[w] = ft_strdup(matches[0]);
				m = 1;
				while (matches[m])
				{
					words = str_to_array(words, ft_strdup(matches[m]));
					m++;
				}
				free_ar((void **)matches);
				free(pattern);
			}
		}
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

static char	**handle_unquoted(char *s, int *i, char **words)
{
	int		start;
	char	*segm;
	int		w;

	start = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	segm = ft_substr(s, start, *i - start);
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
	words = glob_words(words);
	return (words);
}
