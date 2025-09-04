/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:28:17 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/04 15:19:53 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	matches_extension(char *extension, char *file_name)
{
	if(!*extension)
		return (!*file_name);
	if (*extension == '*')
	{
		while (*extension == '*')
			extension++;
		if (!*extension)
			return (1);
		while (*file_name)
		{
			if (matches_extension(extension, file_name))
				return (1);
			file_name++;
		}
		return (0);
	}
	if (*extension == *file_name)
		return (matches_extension(extension + 1, file_name + 1));
	return (0);
}

char	**expand_wildcard(char *extension)
{
	DIR				*dir;
	int				hidden;
	char			*res;
	char			*tmp;
	char			**splitted;
	struct dirent	*entry;

	//porfavor muda isto senao meu eu do futuro mata se
	dir = opendir(".");
	if (!dir)
		return (NULL);
	res = ft_strdup("");
	hidden = (extension[0] == '.');
	while ((entry = readdir(dir)))
	{
		if (!hidden && entry->d_name[0] == '.')
			continue ;
		if (matches_extension(extension, entry->d_name))
		{
			tmp = res;
			res = ft_strjoin(res, entry->d_name);
			free(tmp);
			tmp = res;
			res = ft_strjoin(res, " ");
			free(tmp);
		}
	}
	closedir(dir);
	if (!*res)
		return (free(res), NULL);
	tmp = ft_strtrim(res, " ");
	free(res);
	res = tmp;
	splitted = ft_split(res, ' ');
	free(tmp);
	return (splitted);
}

static void	handle_env_var(char *content, char *new, int *i, int *k, t_minishell *data)
{
	int		j;
	char	*aux;
	char	*tmp;

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

static void	handle_dollar(char *content, char *new, int *i, int *k, t_minishell *data)
{
	char	*tmp;

	(*i)++;
	if (!content[*i])
	{
		new[(*k)++] = '$';
		return ;
	}
	if (content[*i] == '?')
	{
		tmp = ft_itoa(data->exit_code);
		ft_memcpy(new + *k, tmp, ft_strlen(tmp));
		*k = *k + ft_strlen(tmp);
		free(tmp);
		(*i)++;
	}
	else if (ft_isalnum(content[*i]) || content[*i] == '_')
		handle_env_var(content, new, i, k, data);
	else
	{
		new[(*k)++] = '$';
		new[(*k)++] = content[(*i)++];
	}
}

char	*expand_nodes(char *content, t_minishell *data)
{
	int		len;
	char	*res;
	int		i;
	int		k;

	if (!content)
		return (NULL);
	len = get_expanded_len(content, data);
	res = malloc(len + 1);
	i = 0;
	k = 0;
	while (content && content[i])
	{
		if (content[i] == '$')
			handle_dollar(content, res, &i, &k, data);
		else
			res[k++] = content[i++];
	}
	res[k] = '\0';
	return (res);
}
