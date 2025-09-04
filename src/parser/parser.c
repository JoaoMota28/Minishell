/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:57 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/04 02:04:39 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_tree(t_token_list *list, int target_level, int max_level)
{
	t_token_list	*tmp;

	if (!list)
		return (NULL);
	tmp = list;
	while (tmp)
	{
		if (tmp->subshell_level == target_level &&  tmp->token_type == OR)
			return (split_and_build(tmp, list, tmp->token_type, target_level, max_level));
		tmp = tmp->next;
	}
	tmp = list;
	while (tmp)
	{
		if (tmp->subshell_level == target_level && tmp->token_type == AND)
			return (split_and_build(tmp, list, tmp->token_type, target_level, max_level));
		tmp = tmp->next;
	}
	tmp = list;
	while (tmp)
	{
		if (tmp->subshell_level == target_level && tmp->token_type == PIPE)
			return (split_and_build(tmp, list, PIPE, target_level, max_level));
		tmp = tmp->next;
	}
	tmp = list;
	while (tmp)
	{
		if (tmp->subshell_level == target_level && (tmp->token_type == R_IN || tmp->token_type == R_OUT 
				|| tmp->token_type == AP_R_OUT 
				|| tmp->token_type == HERE_DOC))
				return (split_and_build(tmp, list, tmp->token_type, target_level, max_level));
		tmp = tmp->next;
	}
	if (target_level < max_level)
		return (build_tree(list, target_level + 1, max_level));
	return (build_word_node(list, target_level, max_level));
}

static int	get_max_subshell_level(t_token_list *list)
{
	int	max;

	max = 0;
	while (list)
	{
		if (list->subshell_level > max)
			max = list->subshell_level;
		list = list->next;
	}
	return (max);
}

static t_token_list	*strip_paretheses(t_token_list *list)
{
	t_token_list	*cur;
	t_token_list	*next;
	t_token_list	*prev;

	if (!list)
		return (NULL);
	cur = list;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		if (cur->token_type == SUBSHELL)
		{
			if (prev)
				prev->next = next;
			else
				list = next;
			/*if (cur->content)
				free(cur->content);*/
			free(cur);
		}
		else
			prev = cur;
		cur = next;
	}
	return (list);
}

int	parser(t_minishell *data, t_token_list *list)
{
	t_tree	*root;
	int		max_level;

	if (!list)
		return (-1);
	list = strip_paretheses(list);
	max_level = get_max_subshell_level(list);
	root  = build_tree(list, 0, max_level);
	if (!root)
		return (-1);
	//print_tree(root, 0, NULL);
	return (executor(data, root));
}
