/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:49:28 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/05 12:30:21 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_export(t_minishell *data)
{
	int		i;
	char	**arr;
	char	*str;

	i = -1;
	insertion_sort(data->export);
	while (data->export[++i])
	{
		if (!ft_strncmp(data->export[i], "_=", 2))
			continue ;
		arr = ft_split(data->export[i], '=');
		str = ft_strchr(data->export[i], '=');
		if (arr[1])
		{
			printf("declare -x %s=\"", arr[0]);
			if (++str)
				printf("%s", str);
			printf("\"\n");
		}
		else
		{
			printf("declare -x %s=\n", arr[0]);
		}
		free_ar((void **)arr);
	}
}

int	non_identifier_char(char *content)
{
	int	i;

	i = 0;
	if (!content || !content[0])
		return (ft_putstr_fd(EXPORT_PREFIX, 2),
			ft_putstr_fd(content, 2),
			ft_putstr_fd(EXPORT_INVALID, 2), 1);
	if (!ft_isalpha(content[0]) && content[0] != '_')
		return (ft_putstr_fd(EXPORT_PREFIX, 2),
			ft_putstr_fd(content, 2),
			ft_putstr_fd(EXPORT_INVALID, 2), 1);
	while (content[i] && content[i] != '=')
	{
		if (!ft_isalnum(content[i]) && content[i] != '_')
			return (ft_putstr_fd(EXPORT_PREFIX, 2),
				ft_putstr_fd(content, 2),
				ft_putstr_fd(EXPORT_INVALID, 2), 1);
		i++;
	}
	return (0);
}

int	export_aux(t_minishell *data, char *content)
{
	char	**arr;
	char	*str;

	if (non_identifier_char(content))
		return (EXIT_FAILURE);
	arr = ft_split(content, '=');
	str = ft_strchr(content, '=');
	if (str)
	{
		if (fetch_val(data->envp, arr[0]))
			replace_val(&data->envp, arr[0], ++str);
		else
			add_val(&data->envp, arr[0], ++str);
	}
	if (fetch_val(data->export, arr[0]) && str)
		replace_val(&data->export, arr[0], str);
	else if (!fetch_val(data->export, arr[0]))
		add_val(&data->export, arr[0], str);
	free_ar((void **)arr);
	return (EXIT_SUCCESS);
}

int	export_builtin(t_minishell *data, t_tree *leaf)
{
	int	exit_code;

	exit_code = 0;
	if (!leaf)
		list_export(data);
	while (leaf)
	{
		exit_code = exit_code | export_aux(data, leaf->content);
		leaf = leaf->right;
	}
	return (exit_code);
}
