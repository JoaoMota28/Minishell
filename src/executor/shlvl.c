/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:37:38 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/06 15:58:12 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shlvl_err(int val)
{
	char	*err;

	err = ft_itoa(val + 1);
	ft_putstr_fd(SHLVL_ERROR_PREFIX, 2);
	ft_putstr_fd(err, 2);
	free(err);
	ft_putstr_fd(SHLVL_ERROR_SUFFIX, 2);
}

char	*shlvl_val(char *oldval)
{
	long	val;
	int		shlvl;

	val = ft_atoi(oldval);
	if (is_within_llong(oldval))
	{
		if (val + 1 >= 1000 && val + 1 <= INT_MAX)
		{
			shlvl_err(val);
			shlvl = 1;
		}
		else if (val < INT_MIN)
			shlvl = 1;
		else if (val < 0 || val >= INT_MAX)
			shlvl = 0;
		else
			shlvl = val + 1;
	}
	else
		shlvl = 1;
	return (ft_itoa(shlvl));
}
