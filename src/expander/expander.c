/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:07:11 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/05 01:30:13 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;

	i = 1;
	if (node->content)
		free(node->content);
	node->content = ft_strdup(splitted[0]);
	tmp = node;
	while (splitted[i])
	{
		tmp->right = malloc(sizeof(*tmp));
		if (!tmp->right)
		{
			free_ar((void **)splitted);
			return ;
		}
		tmp->right->content = ft_strdup(splitted[i]);
		tmp->right->quote_type = UNQUOTED;
		tmp->right->type = WORD;
		tmp->right->left = NULL;
		tmp->right->right = NULL;
		tmp = tmp->right;
		i++;
	}
	free_ar((void **)splitted);
}

static void	handle_unquoted(t_tree *node, char *expanded)
{
	char	**splitted;

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
	if (node->quote_type == UNQUOTED && ft_strchr(expanded, ' '))
	{
		splitted = ft_split(expanded, ' ');
		free(expanded);
		append_splitted_tokens(node, splitted);
	}
	else
		node->content = expanded;
}

void	expander(t_tree *node, t_minishell *data)
{
	char	*expanded;

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
	handle_unquoted(node, expanded);
	expander(node->right, data);
}
