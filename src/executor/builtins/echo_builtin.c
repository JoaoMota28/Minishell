/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:15:56 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/16 17:45:26 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_handler(char *str) {
	int	i;

	i = 0;
	if (!str || str[i] != '-' || !str[i + 1])
		return (0);
	while (str[++i]) {
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}
 
int	echo_builtin(t_minishell *data, t_tree *leaf)
{
	int	handler;
	int	flag;

	flag = 0;
	handler = 1;
	(void)data;
	while (leaf)
	{
		if (leaf->content[0] != '-')
			handler = 0;
		if (handler && flag_handler(leaf->content))
			flag = 1;
		else
		{
			handler = 0;
			ft_putstr_fd(leaf->content, 1);
			if (leaf->right)
				ft_putstr_fd(" ", 1);
		}
		leaf = leaf->right;
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
