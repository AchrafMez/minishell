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
#include<fcntl.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>
#include<sys/stat.h>
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
typedef struct s_env {
	char			*key;
	char			*value;
	int				dx;
	struct s_env	*next;
}	t_env;


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
int cd(char **args, t_env *env);
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

void print_command(t_command *command);
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


















//----------------------------baattaaaagi---------------------------------
typedef struct t_extra
{
	int		i;
	int		size;
	int		*pid;
	int		**tube;
	char	**path;
	char	**envp;
}	t_extra;

typedef struct ex_er
{
	int	ex;
	int	er;
}	t_exer;
t_exer g_glb;

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}	t_list;

void	handle_child(t_command	*cmd, t_env **env, t_extra ptr);
void	input_command(t_red *in, t_extra ptr, char **cmd);
void	output_command(t_red *out, t_extra ptr);
void	assaining_in(t_red *tmp);
int	assining_out(t_red *tmp, int	*fd);
void	condition_dup(t_extra ptr);
int	closingB(int **tube, int pos);
void	handle_exec(char **path, t_command	*list, t_env **env, char **envp);
int	there_is_slash(char *arg);
void	slash_exec(char **arg, char **envp);
void	command_not_found(char **arg, char *str, int ex);


// ...................................................
//allocptr.............................................
void	allocptr(t_extra *ptr, t_env **tmp, t_env **env);
char	**env_to_envp(t_env **env);
t_env	*getEnvarement(t_env **env, char *key);
void	Tslash(char **path);
int	size_env(t_env	**env);
// ...................................................
//main.............................................
t_env	*get_env(char **env);
void	check_Opwd(char **str);
int	**prc_allocation(int size);
void	execution(t_command **list, t_env **env);
int	**builtins_tube(t_command **list, t_env **env, int size);
int	is_builting(t_command *cmd);
void	exec_builtins(t_command *cmd,t_env  **env);
int	open_files(int *fd, t_command*cmd);
int	output_builtins(t_red *out);
int	input_builtins(t_red *in);
int out_fd_assign(t_red *tmp, int *fd);
void	duplicate_fd(int *ret, int fd);
int **alloc_tube(int size);
int	open_pipes(int **tube, int size);

// ...................................................
// builtins.............................................
// void	ft_cd(t_env **env, char **arg);
// void	ft_echo(char **arg);
// void	ft_env(t_env **env, char **arg);
// void	ft_exit(char **cmd);
// void	ft_export(t_env **env, char **args);
// void	ft_pwd(t_env *env);
// void	ft_unset(t_env **env, char **unset);

// ...................................................
//cleaning.............................................
void	free_tab(char **tab);
void	ft_free_wait(t_extra ptr);
// ...................................................
// libft.............................................
// int	ft_strcmp(const char *s1, char *s2);
// size_t	ft_strlen(const char *s);
// static int	nbrarray(char const *s, char c) ;
void	frealltab(char **str);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// static int	checkimpli(char const *s, char **str, char c);
// char	**ft_split(char const *s, char c);
// char	*ft_strjoin(char const *s1, char const *s2);
int	ft_size_list(t_command *list);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front_env(t_env **lst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *value);
void	*ft_memcpy(void *dest, const void *src, size_t n);
// char	*ft_strdup(const char *s);
char	**ft_strplit(char *env);
// int	ft_atoi(const char *str);
void	export_error(char *exp);
int	condition_name(char *c);
void	free_env(t_env *node);
void	env_del(t_env *lst);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strchr(const char *str, int character);
#endif