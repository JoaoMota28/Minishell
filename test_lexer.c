/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:24:08 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/06 00:32:09 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// static const char *tok_name(int type)
// {
//     if (type == PIPE)      return "PIPE";
//     if (type == R_IN)      return "R_IN";
//     if (type == R_OUT)     return "R_OUT";
//     if (type == AP_R_OUT)  return "AP_R_OUT";
//     if (type == HERE_DOC)  return "HERE_DOC";
//     if (type == WORD)      return "WORD";
//     return "UNKNOWN";
// }

// int main(void)
// {
//     char *line = "ola           >   >   > out 1 2 3 ||  |||\0";
//     t_token_list *tok, *head;

//     printf("Input: %s\n\n", line);

//     head = lexer(line);
//     if (!head)
//     {
//         printf("lexer failed\n");
//         return 1;
//     }

//     printf("Tokens:\n");
//     tok = head;
//     while (tok)
//     {
//         printf(" Token Type: %s\n Content: %s\n\n", 
//              tok_name(tok->token_type), tok->content);
//         tok = tok->next;
//     }
//     return 0;
// }