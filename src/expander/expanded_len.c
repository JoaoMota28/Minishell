/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:19:51 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/25 18:18:00 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_variable_len(char *content, int *i, t_minishell *data)
{
	char	*tmp;
	char	*value;
	int		var_len;
	int		len;

	if (ft_isdigit(content[*i]))
	{
		tmp = ft_substr(content, *i, 1);
		value = ft_strdup(get_env(data->envp, tmp));
		len = ft_strlen(value);
		(*i)++;
		return (free(tmp), free(value), len);
	}
	var_len = 0;
	while (ft_isalnum(content[*i + var_len]) || content[*i + var_len] == '_')
		var_len++;
	tmp = ft_substr(content, *i, var_len);
	value = ft_strdup(get_env(data->envp, tmp));
	len = ft_strlen(value);
	free(tmp);
	free(value);
	*i += var_len;
	return (len);
}

static int	handle_dollar_len(char *content, int *i, t_minishell *data)
{
	int		len;
	char	*tmp;

	len = 0;
	(*i)++;
	if (!content[*i])
		return (1);
	if (content[*i] == '"' || content[*i] == '\'')
		return (0);
	if (content[*i] == '?')
	{
		tmp = ft_itoa(data->exit_code);
		len += ft_strlen(tmp);
		free(tmp);
		(*i)++;
	}
	else if (ft_isalnum(content[*i]) || content[*i] == '_')
		len += handle_variable_len(content, i, data);
	else
	{
		len += 2;
		(*i)++;
	}
	return (len);
}

static int	handle_double_len(char *content, int *i, t_minishell *data)
{
	int	len = 0;

	(*i)++;
	while (content[*i] && content[*i] != '"')
	{
		if (content[*i] == '$')
			len += handle_dollar_len(content, i, data);
		else
		{
			len++;
			(*i)++;
		}
	}
	if (content[*i] == '"')
		(*i)++;
	return (len);
}

int	get_exp_length(char *content, t_minishell *data)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (content && content[i])
	{
		if (content[i] == '\'')
		{
			i++;
			while (content && content[i] && content[i] != '\'')
			{
				len++;
				i++;
			}
			if (content[i] == '\'')
				i++;
		}
		else if (content[i] == '"')
			len += handle_double_len(content, &i, data);
		else if (content[i] == '$')
			len += handle_dollar_len(content, &i, data);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
