/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:07:11 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/02 13:38:21 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_index(int *i, int *j, char *raw, int *q)
{
	if (*q && raw[*j])
		*i = *j + 1;
	else
		*i = *j;
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
	char			*expanded;
	t_quote_type	orig_q;

	if (!node || node->type != WORD)
		return ;
	if (!node->content)
		return ;
	orig_q = detect_quote_type(node->content);
	expanded = expand_quote(node->content, data);
	if (!expanded)
		return ;
	free(node->content);
	node->content = NULL;
	if (orig_q != UNQUOTED)
	{
		node->quote_type = orig_q;
		node->content = expanded;
	}
	else
	{
		node->quote_type = UNQUOTED;
		handle_unquoted(node, expanded);
	}
	expander(node->right, data);
}
