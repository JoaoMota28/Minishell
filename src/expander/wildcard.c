/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:59:43 by jomanuel          #+#    #+#             */
/*   Updated: 2025/10/15 14:18:13 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**is_wc(char **words, int w)
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

char	**expand_unq_wildcard(char *pattern)
{
	char	**matches;

	matches = expand_wildcard(pattern);
	if (!matches)
	{
		matches = malloc(sizeof(char *) * 2);
		if (!matches)
			return (NULL);
		matches[0] = ft_strdup(pattern);
		matches[1] = NULL;
	}
	return (matches);
}

static int	matches_extension(char *extension, char *file_name)
{
	if (!*extension)
		return (!*file_name);
	if (*extension == '*')
	{
		while (*extension == '*')
			extension++;
		if (!*extension)
			return (1);
		while (*file_name)
		{
			if (matches_extension(extension, file_name))
				return (1);
			file_name++;
		}
		return (0);
	}
	if (*extension == *file_name)
		return (matches_extension(extension + 1, file_name + 1));
	return (0);
}

char	*dir_wildcard(char *extension, DIR *dir, char *res)
{
	char			*tmp;
	int				hidden;
	struct dirent	*entry;

	hidden = (extension[0] == '.');
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!hidden && entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (matches_extension(extension, entry->d_name))
		{
			tmp = res;
			res = ft_strjoin(res, entry->d_name);
			free(tmp);
			tmp = res;
			res = ft_strjoin(res, "\037");
			free(tmp);
		}
		entry = readdir(dir);
	}
	return (closedir(dir), res);
}

char	**expand_wildcard(char *extension)
{
	char			*res;
	char			*tmp;
	char			**splitted;
	DIR				*dir;

	tmp = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	res = ft_strdup("");
	res = dir_wildcard(extension, dir, res);
	if (res && !*res)
		return (free(res), NULL);
	tmp = ft_strtrim(res, "\037");
	free(res);
	res = tmp;
	splitted = ft_split(res, 31);
	free(tmp);
	return (splitted);
}
