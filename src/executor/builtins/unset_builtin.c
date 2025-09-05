/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:49:30 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/05 12:31:01 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_loop(char ***arr, char *search, char **new)
{
	int		i;
	int		j;
	int		n;
	char	*tmp;

	i = -1;
	j = -1;
	tmp = ft_strjoin(search, "=");
	n = ft_strlen(tmp);
	while ((*arr)[++i])
	{
		if (strncmp(tmp, (*arr)[i], n))
		{
			new[++j] = ft_strdup((*arr)[i]);
			if (!new[j])
				return (free_ar((void **)new), free(tmp));
		}
	}
	new[j + 1] = NULL;
	free(tmp);
}

void	remove_val(char ***arr, char *search)
{
	char	**new;

	new = malloc(sizeof(char *) * (dp_len(*arr) + 1));
	if (!new)
		return ;
	remove_loop(arr, search, new);
	free_ar((void **)*arr);
	*arr = new;
}

int	unset_builtin(t_minishell *data, t_tree *leaf)
{
	if (!leaf)
		return (EXIT_SUCCESS);
	while (leaf)
	{
		remove_val(&data->export, leaf->content);
		remove_val(&data->envp, leaf->content);
		leaf = leaf->right;
	}
	return (EXIT_SUCCESS);
}
