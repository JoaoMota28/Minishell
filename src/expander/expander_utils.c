/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:19:51 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/13 07:49:47 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_name_start(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	is_name_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	last_word_i(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i - 1);
}

char	**str_to_array(char **arr, char *s)
{
	int		count;
	char	**new;
	int		i;

	count = 0;
	if (arr)
	{
		while (arr[count])
			count++;
	}
	new = malloc(sizeof(char *) * (count + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = s;
	new[i + 1] = NULL;
	free(arr);
	return (new);
}

char	*str_append(char *dst, const char *add)
{
	char	*tmp;

	if (!dst)
		dst = ft_strdup("");
	if (!add)
		return (dst);
	tmp = ft_strjoin(dst, add);
	free(dst);
	return (tmp);
}
