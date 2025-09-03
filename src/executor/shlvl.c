/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:37:38 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/28 14:17:07 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shlvl_val(char *oldval)
{
	long	val;
	int		shlvl;

	val = ft_atoi(oldval);
	if (is_within_llong(oldval))
	{
		if (val + 1 == INT_MAX)
		{
			ft_putstr_fd(SHLVL_ERROR, 2);
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
