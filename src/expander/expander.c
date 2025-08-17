/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:45:53 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/09 23:26:43 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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