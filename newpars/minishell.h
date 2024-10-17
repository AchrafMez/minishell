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
    t_token_type type;
    struct s_token *next;
} t_token;


//for the environment
typedef struct s_env{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

void dup_env(char **envp, t_env **env);
void display_env(t_env *tmp);
void ft_free_env(t_env *env);


//token_utils
t_token *create_token(char *value, t_token_type type);
t_token *ret_last_token(t_token **token_list);
void add_token(t_token **token_list, t_token *new_token);
void print_tokens(t_token *token_list);
void ft_tokens_free(t_token *token_list);

//tokenizer
void handle_space(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_double_quote(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env **env);
int handle_single_quote(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env **env);
int handle_pipe(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_red_in(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_red_out(char **cur, char *buffer, int *buf_idx, t_token **token_list);
void handle_dollar(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env **env, int flag);
t_token *tokenize_input(char *input, t_env **env);


//expanding tools
char *get_env_value(t_env *env, char *searsh);

#endif