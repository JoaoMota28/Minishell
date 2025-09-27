/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:57:48 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/23 15:33:17 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(t_token_type type)
{
	return (type == PIPE || type == R_IN || type == R_OUT
		|| type == AP_R_OUT || type == HERE_DOC
		|| type == AND || type == OR || type == SUBSHELL);
}

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
