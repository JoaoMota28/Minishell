/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:45:23 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 12:01:22 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_dollar_name(char *s, int *idx, t_minishell *data)
{
	char	*tmp;
	int		i;
	char	*val;
	char	*env;

	i = 1;
	val = NULL;
	if (!is_name_start(s[i]))
	{
		tmp = ft_substr(s, i, 1);
		val = ft_strjoin("$", tmp);
		return (*idx = 2, free(tmp), val);
	}
	while (is_name_char(s[i]))
		i++;
	tmp = ft_substr(s, 1, i - 1);
	env = get_env(data->envp, tmp);
	free(tmp);
	*idx = i;
	if (env && env[0])
		return (ft_strdup(env));
	else
		return (NULL);
}

char	*expand_dollar(char *s, int *idx, t_minishell *data)
{
	if (!s[1])
		return (*idx = 1, ft_strdup("$"));
	if (s[1] == '"' || s[1] == '\'')
		return (*idx = 1, NULL);
	if (s[1] == '?')
		return (*idx = 2, ft_itoa(data->exit_code));
	if (s[1] >= '0' && s[1] <= '9')
	{
		if (s[1] == '0')
			return (*idx = 2, ft_strdup("minishell:3"));
		return (*idx = 2, NULL);
	}
	return (expand_dollar_name(s, idx, data));
}

static int	expand_and_replace(t_tree *node, t_minishell *data)
{
	char	**words;

	if (!node || !node->content)
		return (0);
	words = expand_word(node, node->content, data);
	if (!words)
		return (0);
	return (append_splitted_tokens(node, words));
}

void	expander(t_tree *node, t_minishell *data)
{
	int		counter;
	t_tree	*tmp;

	tmp = node;
	if (!tmp || tmp->type != WORD)
	{
		if (tmp)
		{
			expander(tmp->left, data);
			expander(tmp->right, data);
		}
		return ;
	}
	counter = expand_and_replace(tmp, data);
	while (counter--)
		tmp = tmp->right;
	if (tmp->right)
		expander(tmp->right, data);
	if (data && data->root == node)
		clean_tree(&data->root);
}
