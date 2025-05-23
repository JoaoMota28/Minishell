/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:33:08 by bpires-r          #+#    #+#             */
/*   Updated: 2025/05/23 16:03:06 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../complete_lib/42_Libft/libft.h"
# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Printf/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum s_token_type
{
	PIPE,
	R_IN,
	R_OUT,
	AP_R_OUT,
	HERE_DOC,
	WORD,
}               t_token_type;

typedef struct s_token_list
{
	char                *content;
	struct s_token_list *next;
	t_token_type		token_type;
}               t_token_list;

t_token_list *lexer(char *line);

#endif
