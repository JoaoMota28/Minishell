/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:38:57 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/11 15:59:20 by jomanuel         ###   ########.fr       */
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
	int				file_fd;
	int				subshell_level;
	bool			visited;
	t_token_type	type;
	t_quote_type	quote_type;
}				t_tree;

//tree build
t_tree			*build_tree(t_token_list *list, int level, int max_level);
t_tree			*split_and_build(t_token_list *target, t_token_list *left,
					int level, int max_level);
t_tree			*build_word_node(t_token_list *list, int level, int max_level);
//void			print_tree(t_tree *node, int level, char *leaf);
#endif