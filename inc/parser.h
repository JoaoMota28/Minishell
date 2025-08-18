/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:38:57 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/18 16:16:15 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../complete_lib/42_Libft/libft.h"
# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Printf/ft_printf.h"
# include "lexer.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_tree
{
	struct s_tree	*subshell;
	struct s_tree	*left;
	struct s_tree	*right;
	char			*content;
	t_token_type	type;
	int				visited;
}				t_tree;

//tree build
t_tree	*build_tree(t_token_list *list);
t_tree	*split_and_build(t_token_list *target, t_token_list *left, t_token_type type);
t_tree	*build_word_node(t_token_list *list);
void 	print_tree(t_tree *node, int level, char *leaf);

#endif