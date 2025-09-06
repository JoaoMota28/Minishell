/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:28:17 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/06 15:59:55 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_env_var(char *cont, char *new, int *vals, t_minishell *data)
{
	int		j;
	char	*aux;
	char	*tmp;

	if (ft_isdigit(cont[vals[0]]))
	{
		aux = ft_substr(cont, vals[0], 1);
		(vals[0])++;
	}
	else
	{
		j = 0;
		while (cont[vals[0] + j]
			&& (ft_isalnum(cont[vals[0] + j]) || cont[vals[0] + j] == '_'))
			j++;
		aux = ft_substr(cont, vals[0], j);
		vals[0] = vals[0] + j;
	}
	tmp = ft_strdup(get_env(data->envp, aux));
	ft_memcpy(new + vals[1], tmp, ft_strlen(tmp));
	vals[1] += ft_strlen(tmp);
	free(aux);
	free(tmp);
}

static void	handle_dollar(char *cont, char *new, int *vals, t_minishell *data)
{
	char	*tmp;

	(vals[0])++;
	if (!cont[vals[0]])
	{
		new[(vals[1])++] = '$';
		return ;
	}
	if (cont[vals[0]] == '?')
	{
		tmp = ft_itoa(data->exit_code);
		ft_memcpy(new + vals[1], tmp, ft_strlen(tmp));
		vals[1] = vals[1] + ft_strlen(tmp);
		free(tmp);
		(vals[0])++;
	}
	else if (ft_isalnum(cont[vals[0]]) || cont[vals[0]] == '_')
		handle_env_var(cont, new, vals, data);
	else
	{
		new[(vals[1])++] = '$';
		new[(vals[1])++] = cont[(vals[0])++];
	}
}

char	*expand_nodes(char *content, t_minishell *data)
{
	int		len;
	char	*res;
	int		*vals;

	if (!content)
		return (NULL);
	len = get_expanded_len(content, data);
	res = malloc(len + 1);
	vals = malloc(2 * sizeof(int));
	if (!res || !vals)
		return (NULL);
	vals[0] = 0;
	vals[1] = 0;
	while (content && content[vals[0]])
	{
		if (content[vals[0]] == '$')
			handle_dollar(content, res, vals, data);
		else
			res[vals[1]++] = content[vals[0]++];
	}
	res[vals[1]] = '\0';
	free(vals);
	return (res);
}
