#ifndef MINISHELL_H
#define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
// #include "../execution/builting/builtin.h"
typedef enum e_token_type {
    WORD, //0
    S_QUOTE, //1
    D_QUOTE, //2
    SPACES, //3
    ENV, //4
    PIPE, //5
    RED_IN, //6
    RED_OUT, //7
    RED_APP, //8
    HERE_DOC //9
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



typedef struct s_red{
    char *value;
    t_token_type type;
    struct s_red *next;
    
} t_red;

typedef struct s_command{
    char **args;
    char *path;
    t_red *in;
    t_red *out;
    struct s_command *next;
} t_command;


//token_utils
t_token *create_token(char *value, t_token_type type);
t_token *ret_last_token(t_token **token_list);
void add_token(t_token **token_list, t_token *new_token);
void print_tokens(t_token *token_list);
void ft_tokens_free(t_token *token_list);
void tokens_edit(t_token **token_list);
void delete_space(t_token **token_list);

//----------------------------tokenizer-----------------//
void handle_space(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_double_quote(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env *env);
int handle_single_quote(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env *env);
int handle_pipe(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_red_in(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_red_out(char **cur, char *buffer, int *buf_idx, t_token **token_list);
void handle_dollar(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env **env, int flag);
t_token *tokenize_input(char *input, t_env **env);


//env
void dup_env(char **envp, t_env **env);
void display_env(t_env *tmp);
void ft_free_env(t_env **env);


//expanding tools
char *get_env_value(t_env *env, char *searsh);


//---------------------------parser--------------------//
//cmd utils
t_command *create_command();
void add_arg(char ***args, int *arg_count, char *value);
void add_red(t_red **red_list, char *value, t_token_type type);
void free_cmd(t_command *command);

void print_cmd(t_command *command);
t_command *fill_cmd_assit1(t_command **cmd_list);
void fill_cmd_assit(t_token *token, t_command *cmd, int *arg_count);
t_command *fill_command(t_token *tokens);


//path
void set_path(t_command **cmd);
char *get_path(char *target);
void free_path(char **path);


void handl_input(t_env **env);


//signal
void ctrl_c(int sig);
void ctrl_d();
void handle_signals(void);

int ft_strcmp(char *str, char *target);
#endif