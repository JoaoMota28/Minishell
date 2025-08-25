/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:28:17 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/25 18:19:21 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_single(char *content, char *new, int *i, int *k)
{
	(*i)++;
	while (content[*i] && content[*i] != '\'')
		new[(*k)++] = content[(*i)++];
	if (content[*i] == '\'')
		(*i)++;
}

static void	handle_dollar(char *content, char *new, int *i, int *k, t_minishell *data)
{
	char	*tmp;
	char	*aux;
	int		j;

	(*i)++;
	if (!content[*i])
	{
		new[(*k)++] = '$';
		return ;
	}
	if (content[*i] == '"' || content[*i] == '\'')
		return ;
	if (content[*i] == '?')
	{
		tmp = ft_itoa(data->exit_code);
		ft_memcpy(new + *k, tmp, ft_strlen(tmp));
		*k = *k + ft_strlen(tmp);
		free(tmp);
		(*i)++;
	}
	else if (ft_isalnum(content[*i]) || content[*i] == '_')
	{
		if (ft_isdigit(content[*i]))
		{
			aux = ft_substr(content, *i, 1);
			(*i)++;
		}
		else
		{
			j = 0;
			while (content[*i + j] && 
				(ft_isalnum(content[*i + j]) || content[*i + j] == '_'))
				j++;
			aux = ft_substr(content, *i, j);
			*i = *i + j;
		}
		tmp = ft_strdup(get_env(data->envp, aux));
		ft_memcpy(new + *k, tmp, ft_strlen(tmp));
		*k += ft_strlen(tmp);
		free(aux);
		free(tmp);
	}
	else
	{
		new[(*k)++] = '$';
		new[(*k)++] = content[(*i)++];
	}
}

static void	handle_double(char *content, char *new, int *i, int *k, t_minishell *data)
{
	(*i)++;
	while (content[*i] && content[*i] != '"')
	{
		if (content[*i] == '$')
			handle_dollar(content, new, i, k, data);
		else
			new[(*k)++] = content[(*i)++];
	}
	if (content[*i] == '"')
		(*i)++;
}


char	*expand_token(char *content, t_minishell *data)
{
	char	*new;
	int		len;
	int		i;
	int		k;

	len = get_exp_length(content, data);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return NULL;
	i = 0;
	k = 0;
	while (content && content[i])
	{
		if (content[i] == '\'')
			handle_single(content, new, &i, &k);
        else if (content[i] == '"')
            handle_double(content, new, &i, &k, data);
		else if (content[i] == '$')
			handle_dollar(content, new, &i, &k, data);
        else 
            new[k++] = content[i++];
	}
    new[k] = '\0';
    return (new);
}
