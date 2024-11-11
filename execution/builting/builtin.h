#ifndef BUILTIN_H
#define BUILTIN_H
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>
// <<<<<<< HEAD
// #include"./libft/libft.h"
// =======
// #include"../../newpars/libft/libft.h"
// >>>>>>> ae8c0bf (merge conf)

// #define HERE_DOC 1
// #define WORD 2
// typedef struct s_env {
//     char *key;  
//    char *value;  

//     struct s_env *next;   
// } t_env;

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
typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}	t_list;
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

typedef struct s_cmd{
    char **args;
    char *path;
    t_red *red;
    t_red *red_out;
    struct s_cmd *next;
} t_cmd;

// exec
typedef struct ex_er
{
	int	ex;
	int	er;
}	t_exer;
typedef struct t_extra
{
	int		i;
	int		size;
	int		*pid;
	int		**tube;
	char	**path;
	char	**envp;
}	t_extra;

int	cd_var(char *var, t_env **env);
void	ft_echo(char **arg);
t_env ft_env(char **env, char **arg);
void	ft_exit(char **cmd);
t_env	ft_export(char **argv, char **env);
static void	process_heredocs(t_cmd *cmd, t_env *env);
void	ft_pwd(t_env *env);
void	ft_unset(t_env **env, t_cmd *cmd);

#endif