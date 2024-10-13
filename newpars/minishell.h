#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type {
    WORD,
    S_QUOTE,
    D_QUOTE,
    SPACES,
    ENV,
    PIPE,
    RED_IN,
    RED_OUT,
    RED_APP,
    HERE_DOC
} t_token_type;


typedef struct s_token{
    char *value;
    int type;
    struct s_token *next;
} t_token;

//token_utils
t_token *create_token(char *value, t_token_type type);
t_token *ret_last_token(t_token **token_list);
void add_token(t_token **token_list, t_token *new_token);
void print_tokens(t_token *token_list);
void ft_tokens_free(t_token *token_list);
#endif