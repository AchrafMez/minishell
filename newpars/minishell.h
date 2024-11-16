#ifndef MINISHELL_H
#define MINISHELL_H

#include <fcntl.h>
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
    HERE_DOC, //9
    EXIT_STATUE
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
    char *name;
    char **args;
    char *path;
    t_red *in;
    t_red *out;
    struct s_command *next;
} t_command;

//for the exit status
typedef struct s_shell{
    int exit_status;
    t_env *env;
} t_shell;


//just for the norm
typedef struct s_content
{
    char **cur;
    char *buffer;
    int *buf_idx;
    t_token **token_list;
    t_env *env;
} t_content;

//-----------------------------exec-----------------------------//
void exec_built(t_command *cmd, t_env **env);
int is_built_in(t_command *command);
//built_in
void cd(char **args, t_env *env);
int echo(char **args);
int pwd(void);
int ft_env(char **args, t_env *env);
//export
int is_valid_key(char *arg);
void print_export(t_env *env);
void print_export(t_env *env);
t_env *find(t_env *env, char *key);
void set_export_env(t_env **env, char *key, char *value);
int export(char **args, t_env **env);
//unset
int unset(char **args, t_env **env);
int ft_exit(char **args, int last_e_s);


//token_utils
t_token *create_token(char *value, t_token_type type);
t_token *ret_last_token(t_token **token_list);
void add_token(t_token **token_list, t_token *new_token);
void print_tokens(t_token *token_list);
void ft_tokens_free(t_token *token_list);
void tokens_edit(t_token **token_list);
void delete_space(t_token **token_list); 


//----------------------------tokenizer-----------------//
//quotes
int check_single(char **cur, char *buffer, int *buf_idx);
void check_single_for_helper(t_content *content);
int handle_singlequote_helper(t_content *content);
int handle_single_quote(t_content *content);


void handle_double_quote_helper(t_content *content);
int handle_double_quote(t_content *content);

void	handle_dollar_helper(t_content *content, char *expanded, int flag);
void handle_dollar(t_content *content, int flag);
int	handle_quotes(t_content *content);
void handle_space(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_pipe(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_red_in(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int handle_red_out(char **cur, char *buffer, int *buf_idx, t_token **token_list);
int	handle_red(t_content *content);
t_token *tokenize_input(char *input, t_env **env);


//----------------------------env-----------------------/
//env
void dup_env(char **envp, t_env **env);
void display_env(t_env *tmp);
void ft_free_env(t_env **env);


//expanding tools
char *get_env_value(t_env *env, char *searsh);
void set_env_value(t_env **env, char *searsh, char *set);

//---------------------------parser--------------------//
int	check_syntax(t_token *token);
int	check_unclosed_quotes(char *input);
//cmd utils
t_command *create_command();
void add_arg(char ***args, int *arg_count, char *value);
void add_red(t_red **red_list, char *value, t_token_type type);
void free_cmd(t_command *command);

void print_cmd(t_command *command);
t_command *fill_cmd_assit1(t_command **cmd_list);
void fill_cmd_assit(t_token *token, t_command *cmd, int *arg_count, t_env *env);
t_command *fill_command(t_token *tokens, t_env *env);


//path
void set_path(t_command **cmd);
char *get_path(char *target);
void free_path(char **path);


void handl_input(t_env **env, t_shell *shell);


//signal
int ft_strcmp(char *str, char *target);
void ctrl_c(int sig);
void ctrl_d();
void handle_signals(void);


#endif