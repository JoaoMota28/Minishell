/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:49:22 by jomanuel          #+#    #+#             */
/*   Updated: 2025/10/03 20:11:45 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_within_llong(const char *str)
{
	int		negative;
	size_t	len;

	negative = 0;
	if (*str == '-' || *str == '+')
		negative = (*str++ == '-');
	while (*str == '0')
		str++;
	len = ft_strlen(str);
	if (len == 0)
		return (1);
	if (len > 19)
		return (0);
	if (len < 19)
		return (1);
	if (negative)
		return (ft_strcmp(str, EXIT_ABS_MIN) <= 0);
	else
		return (ft_strcmp(str, EXIT_MAX) <= 0);
}

static int	is_valid_arg(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
		return (0);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	exit_builtin(t_minishell *data, t_tree *leaf)
{
	int	exit_code;

	if (data->exec.pipeline_child)
		exit_msh(data, 0);
	ft_putstr_fd("exit\n", 1);
	if (!leaf)
		return (data->exit_code);
	if (!is_valid_arg(leaf->content) || !is_within_llong(leaf->content))
	{
		ft_putstr_fd(EXIT_PREFIX, 2);
		ft_putstr_fd(leaf->content, 2);
		ft_putstr_fd(EXIT_NON_NUMERIC, 2);
		return (2);
	}
	if (leaf->right)
	{
		ft_putstr_fd(EXIT_ARGS, 2);
		return (1);
	}
	exit_code = ft_atol(leaf->content);
	return ((unsigned char)exit_code);
}
