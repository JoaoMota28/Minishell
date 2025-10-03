/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:57:48 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/03 01:25:35 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **envp, char *name)
{
	size_t	n;
	size_t	i;

	i = 0;
	n = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, n) && envp[i][n] == '=')
			return (envp[i] + n + 1);
		i++;
	}
	return ("");
}

int	dp_len(char **dp)
{
	int	len;

	if (!dp)
		return (0);
	len = 0;
	while (dp[len])
		len++;
	return (len);
}

char	**dp_dup(char **dp)
{
	int		i;
	int		len;
	char	**new;

	i = 0;
	len = dp_len(dp);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	while (dp[i])
	{
		new[i] = ft_strdup(dp[i]);
		if (!new)
			return (free_ar((void **)new), NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

static void	handle_copy(char *content, int *i, char *res, int *k)
{
	char	q;

	q = 0;
	while (content[*i])
	{
		if (content[*i] == '\'' || content[*i] == '"')
		{
			if (!q)
			{
				q = content[(*i)++];
				continue ;
			}
			else if (content[*i] == q)
			{
				q = 0;
				(*i)++;
				continue ;
			}
		}
		res[(*k)++] = content[(*i)++];
	}
}

char	*strip_quotes(char *content)
{
	int		i;
	int		k;
	char	*res;

	i = 0;
	k = 0;
	res = malloc(ft_strlen(content) + 1);
	if (!res)
		return (NULL);
	handle_copy(content, &i, res, &k);
	res[k] = '\0';
	return (res);
}
