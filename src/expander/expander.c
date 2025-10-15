/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:45:23 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/15 09:48:29 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_dollar_rules(char *tmp, t_minishell *data, int *idx, char *s)
{
	char	*val;
	int		i;

	i = 1;
	val = NULL;
	if (s[i] == '?')
	{
		tmp = ft_itoa(data->exit_code);
		return (*idx = 2, tmp);
	}
	if (s[i] >= '0' && s[i] <= '9')
	{
		*idx = 2;
		if (s[i] == '0')
			return (ft_strdup("minishell:3"));
		return (NULL);
	}
	if (!is_name_start(s[i]))
	{
		tmp = ft_substr(s, i, 1);
		val = ft_strjoin("$", tmp);
		free(tmp);
		return (*idx = 2, val);
	}
	return (NULL);
}


char	*expand_dollar(char *s, int *idx, t_minishell *data)
{
	char	*val;
	char	*tmp;
	char	*env;
	int		i;
	int		start; 

	i = 1;
	val = NULL;
	if (!s[i])
		return (*idx = 1, ft_strdup("$"));
	if (s[i] == '"' || s[i] == '\'')
		return (*idx = 1, NULL);
	if (s[i] == '?')
		return (check_dollar_rules(tmp, data, idx, s));
	if (s[i] >= '0' && s[i] <= '9')
		return (check_dollar_rules(tmp, data, idx, s));
	if (!is_name_start(s[i]))
		return (check_dollar_rules(tmp, data, idx, s));
	//separar
	start = i;
	while (is_name_char(s[i]))
		i++;
	tmp = ft_substr(s, start, i - start);
	env = get_env(data->envp, tmp);
	free(tmp);
	if (env && env[0])
		val = ft_strdup(env);
	else
		val = NULL;
	*idx = i;
	return (val);
}

static int	expand_and_replace(t_tree *node, t_minishell *data)
{
	char	**words;

	if (!node || !node->content)
		return (0);
	words = expand_word(node, node->content, data);
	if (!words)
		return (1);
	append_splitted_tokens(node, words);
	return (0);
}

void	expander(t_tree *node, t_minishell *data)
{
	int		del;
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
	del = expand_and_replace(tmp, data);
	if (del)
	{
		free(tmp->content);
		tmp->content = ft_strdup("");
	}
	if (tmp->right)
		expander(tmp->right, data);
	if (data && data->root == node)
		clean_tree(&data->root);
}
