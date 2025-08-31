/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:38:57 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/31 14:27:10 by bpires-r         ###   ########.fr       */
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
	struct s_tree	*left;
	struct s_tree	*right;
	char			*content;
	int				pipe_hd[2];
	int				subshell_level;
	bool			visited;
	t_token_type	type;
	t_quote_type	quote_type;
}				t_tree;

//tree build
t_tree			*build_tree(t_token_list *list, int level, int max_level);
t_tree			*split_and_build(t_token_list *target, t_token_list *left, t_token_type type, int level, int max_level);
t_tree			*build_word_node(t_token_list *list, int level, int max_level);
void 			print_tree(t_tree *node, int level, char *leaf);
void			set_subshell_level(t_tree *node, int level);
#endif