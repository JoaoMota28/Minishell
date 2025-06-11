/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:57:48 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/10 16:29:27 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

int	is_operator(t_token_type type)
{
	return (type == PIPE || type == R_IN || type == R_OUT
		|| type == AP_R_OUT || type == HERE_DOC);
}

int	dp_len(char **dp)
{
	int	len;

	if (!dp)
		return (0);
	len = 0;
	while(dp[len])
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
