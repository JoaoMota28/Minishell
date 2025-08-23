/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:45:53 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/23 05:41:46 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			*file_name++;
		}
		return (0);
	}
	if (*extension == *file_name)
		return (matches_extension(extension + 1, file_name + 1));
	return (0);
}

char	*expand_wildcard(char *extension)
{
	DIR	*dir;
	struct dirent	*
}

char	*expand_heredoc(char *line, t_tree *delim, t_minishell *data)
{
	char	*expanded;

	if (delim->quote_type)
		return (ft_strdup(line));
	expanded = expand_token(line, data);
	if (!expanded)
		return (ft_strdup(""));
	return (expanded);
}

static void	append_splitted_tokens(t_token_list *node, char **splitted)
{
	t_token_list	*tmp;
	int				i;

	i = 1;
	node->content = ft_strdup(splitted[0]);
	tmp = node;
	while(splitted[i])
	{
		tmp->next = malloc(sizeof(*tmp));
		tmp = tmp->next;
		tmp->content = ft_strdup(splitted[i++]);
		tmp->quote_type = UNQUOTED;
		tmp->token_type = WORD;
		tmp->next = NULL;
	}
	free_ar((void **)splitted);
}

void	expander(t_token_list *node, t_minishell *data)
{
	char		*expanded;
	char		**splitted;

	expanded = expand_token(node->content, data);
	if (node->token_type == WORD)
		free(node->content);
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
	if (!expanded[0] && !node->quote_type)
	{
		free(expanded);
		node->content = NULL;
		return ;
	}
	if (node->quote_type == UNQUOTED && strchr(expanded, ' '))
	{
		splitted = ft_split(expanded, ' ');
		free(expanded);
		append_splitted_tokens(node, splitted);
	}
	else
		node->content = expanded;
	//int i = 1;
	/*while (node)
	{
		printf("Expanded Token %d : [%s]\n", i, node->content);
		i++;
		node = node->next;
	}*/
}
