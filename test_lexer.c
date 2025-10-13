/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:24:08 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/11 20:25:14 by bpires-r         ###   ########.fr       */
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

/* ---------- helpers (no triple pointers) ---------- */

static int last_word_index(char **words)
{
    int i;

    i = 0;
    while (words[i])
        i++;
    return (i - 1);
}

/* All handlers return the (possibly reallocated) char **words pointer.
   Caller must reassign: words = handle_xxx(..., words, ...);
*/

static char **handle_single_quote(const char *s, int *pos, char **words)
{
    int start;
    char *tmp;
    int i;

    start = *pos + 1;
    *pos = start;
    while (s[*pos] && s[*pos] != '\'')
        (*pos)++;
    tmp = ft_substr(s, start, *pos - start);
    i = last_word_index(words);
    words[i] = str_append_free(words[i], tmp);
    free(tmp);
    if (s[*pos] == '\'')
        (*pos)++;
    return (words);
}

static char **handle_double_quote(const char *s, int *pos, char **words, t_minishell *data)
{
    char *tmp;
    int i;

    tmp = expand_double(s, data, pos);
    i = last_word_index(words);
    words[i] = str_append_free(words[i], tmp);
    free(tmp);
    if (s[*pos] == '"')
        (*pos)++;
    return (words);
}

static char **handle_space_sep(const char *s, int *pos, char **words)
{
    int i;

    (void)s;
    (*pos)++;
    i = last_word_index(words);
    if (words[i] && words[i][0] != '\0')
        words = push_str_array(words, ft_strdup(""));
    return (words);
}

static char **handle_dollar(const char *s, int *pos, char **words, t_minishell *data)
{
    char *tmp;
    char **sp;
    int i;
    int m;

    tmp = expand_var_unquoted(s, pos, data);
    if (!tmp)
        return (words);
    sp = split_spaces_safe(tmp);
    free(tmp);
    if (!sp)
        return (words);
    i = last_word_index(words);
    words[i] = str_append_free(words[i], sp[0]);
    m = 1;
    while (sp[m])
    {
        words = push_str_array(words, ft_strdup(sp[m]));
        m++;
    }
    free_str_array(sp);
    return (words);
}

static char **handle_unquoted_chunk(const char *s, int *pos, char **words)
{
    int start;
    char *chunk;
    char **matched;
    int m;
    int i;

    start = *pos;
    while (s[*pos] && s[*pos] != '\'' && s[*pos] != '"' && s[*pos] != ' ')
        (*pos)++;
    chunk = ft_substr(s, start, *pos - start);
    if (ft_strchr(chunk, '*'))
    {
        matched = expand_unquoted_pattern(chunk);
        m = 0;
        while (matched && matched[m])
        {
            i = last_word_index(words);
            if (m == 0)
                words[i] = str_append_free(words[i], matched[m]);
            else
                words = push_str_array(words, ft_strdup(matched[m]));
            m++;
        }
        if (matched)
            free_str_array(matched);
        free(chunk);
        return (words);
    }
    i = last_word_index(words);
    words[i] = str_append_free(words[i], chunk);
    free(chunk);
    return (words);
}

/* ---------- refactored build_words_from_token (no triple pointers) ---------- */

static char **build_words_from_token(const char *s, t_minishell *data)
{
    char *cur;
    char **words;
    int pos;

    if (!s)
        return (NULL);
    cur = ft_strdup("");
    words = NULL;
    words = push_str_array(words, cur); /* words[0] is "" */
    pos = 0;
    while (s[pos])
    {
        if (s[pos] == '\'')
        {
            words = handle_single_quote(s, &pos, words);
            continue;
        }
        if (s[pos] == '"')
        {
            words = handle_double_quote(s, &pos, words, data);
            continue;
        }
        if (s[pos] == ' ')
        {
            words = handle_space_sep(s, &pos, words);
            continue;
        }
        if (s[pos] == '$')
        {
            words = handle_dollar(s, &pos, words, data);
            continue;
        }
        /* unquoted contiguous chunk (until space or quote) */
        words = handle_unquoted_chunk(s, &pos, words);
    } /* end scan */

    /* If final result is single empty string, return a marker that means "remove node" -> NULL */
    if (words && words[0] && !words[0][0])
    {
        free_str_array(words);
        return (NULL);
    }
    return (words);
}
