/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:24:05 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/18 15:17:39 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_val(char **arr, char *s)
{
	int		i;
	int		n;
	char	*fstring;

	i = 0;
	n = ft_strlen(s);
	if (!arr)
		return (NULL);
	fstring = ft_strjoin(s, "=");
	while (arr[i])
	{
		if (!ft_strncmp(fstring, arr[i], n + 1) || !ft_strncmp(s, arr[i], n))
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
	char	*t;
	char	*str;

	t = ft_strjoin(key, "=");
	n = ft_strlen(t);
	i = 0;
	while ((*arr)[i])
	{
		if (!ft_strncmp(t, (*arr)[i], n) || !ft_strncmp(t, (*arr)[i], n - 1))
		{
			str = ft_strjoin(t, val);
			if (!str)
				str = ft_strdup(t);
			free(t);
			t = NULL;
			free((*arr)[i]);
			(*arr)[i] = str;
			break ;
		}
		i++;
	}
	if (t)
		free(t);
}

int	add_val(char ***arr, char *key, char *val, int i)
{
	char	*tmp;
	char	*str;
	char	**new;

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
