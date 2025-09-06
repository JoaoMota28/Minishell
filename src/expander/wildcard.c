/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:59:43 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/06 16:24:49 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			res = ft_strjoin(res, " ");
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
	tmp = ft_strtrim(res, " ");
	free(res);
	res = tmp;
	splitted = ft_split(res, ' ');
	free(tmp);
	return (splitted);
}
