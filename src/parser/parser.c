/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:57 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/28 19:46:34 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_subshell_tree(t_token_list **list)
{
	int				level;
	t_token_list	*start;
	t_token_list	*sub_list;
	t_tree			*sub_tree;

	start = *list;
	*list = start->next;
	level = start->subshell_level;
	free(start->content);
	free(start);
	sub_list = extract_subshell_tokens(list);
	sub_tree = build_tree(sub_list);
	if (sub_tree && sub_list)
		set_subshell_level(sub_tree, level);
	return (sub_tree);
}

t_tree	*build_tree(t_token_list *list)
{
	t_token_list	*tmp;

	if (!list)
		return (NULL);
	tmp = list;
	if (list->token_type == SUBSHELL && list->p_type == P_OPEN)
		return (build_subshell_tree(&list));
	while (tmp)
	{
		if (tmp->token_type == AND || tmp->token_type == OR)
			return (split_and_build(tmp, list, tmp->token_type));
		tmp = tmp->next;
	}
	tmp = list;
	while (tmp)
	{
		if (tmp->token_type == PIPE)
			return (split_and_build(tmp, list, PIPE));
		tmp = tmp->next;
	}
	tmp = list;
	while (tmp)
	{
		if (tmp->token_type == R_IN || tmp->token_type == R_OUT 
				|| tmp->token_type == AP_R_OUT 
				|| tmp->token_type == HERE_DOC)
				return (split_and_build(tmp, list, tmp->token_type));
		tmp = tmp->next;
	}
	return (build_word_node(list));
}

int	parser(t_minishell *data, t_token_list *list)
{
	t_tree	*root;

	root  = build_tree(list);
	if (!root)
		return (-1);
	print_tree(root, 0, NULL);
	return (executor(data, root));
}
