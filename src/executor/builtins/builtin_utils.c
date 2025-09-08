/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:24:05 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/08 16:00:17 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_val(char **arr, char *search)
{
	int		i;
	int		n;
	char	*fstring;

	i = 0;
	n = ft_strlen(search);
	if (!arr)
		return (NULL);
	fstring = ft_strjoin(search, "=");
	while (arr[i])
	{
		if (!ft_strncmp(fstring, arr[i], n + 1) || !ft_strncmp(search, arr[i], n))
			return (free(fstring), arr[i] + n + 1);
		i++;
	}
	free(fstring);
	return (NULL);
}

void	replace_val(char ***arr, char *key, char *val)
{
	int		i;
	int		n;
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(key, "=");
	n = ft_strlen(tmp);
	i = 0;
	while ((*arr)[i])
	{
		if (!ft_strncmp(tmp, (*arr)[i], n) || !ft_strncmp(tmp, (*arr)[i], n - 1))
		{
			str = ft_strjoin(tmp, val);
			if (!str)
				str = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
			free((*arr)[i]);
			(*arr)[i] = str;
			break ;
		}
		i++;
	}
	if (tmp)
		free(tmp);
}

int	add_val(char ***arr, char *key, char *val)
{
	int		i;
	char	*tmp;
	char	*str;
	char	**new;

	i = -1;
	new = malloc(sizeof(char *) * (dp_len(*arr) + 2));
	if (!new)
		return (EXIT_FAILURE);
	while ((*arr)[++i])
	{
		new[i] = ft_strdup((*arr)[i]);
		if (!new[i] && *val)
			return (free_ar((void **)new), EXIT_FAILURE);
	}
	if (val)
		tmp = ft_strjoin(key, "=");
	else
		tmp = ft_strdup(key);
	str = ft_strjoin(tmp, val);
	if (!str)
		str = ft_strdup(tmp);
	new[i] = str;
	new[i + 1] = NULL;
	free_ar((void **)*arr);
	*arr = new;
	return (free(tmp), EXIT_SUCCESS);
}

void	insertion_sort(char **arr)
{
	int		n;
	int		i;
	int		j;
	char	*swap;

	n = dp_len(arr);
	i = 0;
	while (i < n)
	{
		j = i;
		while (j > 0)
		{
			if (ft_strcmp(arr[j], arr[j - 1]) < 0)
			{
				swap = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = swap;
			}
			else
				break ;
			j--;
		}
		i++;
	}
}
