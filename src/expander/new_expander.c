/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:07:11 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/03 15:57:14 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*expand_nodes(char *content, t_minishell *data)
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
}

int	matches_extension(char *extension, char *file_name)
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

char	*expand_heredoc(char *line, t_tree *delim, t_minishell *data)
{
	char	*expanded;

	if (delim->quote_type)
		return (ft_strdup(line));
	expanded = expand_nodes(line, data);
	if (!expanded)
		return (ft_strdup(""));
	return (expanded);
}

static void	append_splitted_tokens(t_tree *node, char **splitted)
{
	t_tree	*tmp;
	int				i;

	if (!node || !splitted)
		return ;
	i = 1;
	if (node->content)
		free(node->content);
	node->content = ft_strdup(splitted[0]);
	tmp = node;
	while(splitted[i])
	{
		tmp->right = malloc(sizeof(*tmp));
		if (!tmp->right)
		{
			free_ar((void **)splitted);
			return ;
		}
		tmp = tmp->right;
		tmp->content = ft_strdup(splitted[i++]);
		tmp->quote_type = UNQUOTED;
		tmp->type = WORD;
		tmp->left = NULL;
		tmp->right = NULL;
	}
	free_ar((void **)splitted);
}

void	expander(t_tree *node, t_minishell *data)
{
	char	*expanded;
	char	**splitted;

	if (!node || node->type != WORD)
		return ;
	if (node->quote_type == SINGLE_O)
		return ;
	if (node->quote_type == DOUBLE_O)
	{
		expanded = expand_nodes(node->content, data);
		if (node->content)
			free(node->content);
		if (expanded)
			node->content = expanded;
		else
			node->content = ft_strdup("");
	}
	expanded = expand_nodes(node->content, data);
	if (node->content)
		free(node->content);
	node->content = NULL;
	if (!expanded)
		return ;
	if (ft_strchr(expanded, '*') && !node->quote_type)
	{
		splitted = expand_wildcard(expanded);
		if (splitted)
		{
			free(expanded);
			append_splitted_tokens(node, splitted);
			return ;
		}
	}
	else
		node->content = expanded;
}
