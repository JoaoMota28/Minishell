/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:45:53 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/11 18:14:17 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_token(char *content, t_minishell *data)
{
	char	*new;
	int		i;
	int		k;

	new = malloc(sizeof(char) * ft_strlen(content) + 1);
	i = 0;
	k = 0;
	while (content[i])
	{
		
		i++;
	}
}

void	expander(t_token_list *node, t_minishell *data)
{
	t_token_list	*tmp;
	char		*expanded;
	char		**tokens;

	if (node->quote_type == SINGLE_O)
		return ;
	expanded = expand_token(node->content, data);
}