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
<<<<<<< HEAD
#include"./libft/libft.h"
=======
#include"../../newpars/libft/libft.h"
>>>>>>> ae8c0bf (merge conf)

#define HERE_DOC 1
typedef struct s_env {
    char *key;  
   char *value;  
    struct s_env *next;   
} t_env;

typedef struct s_cmd {
    int type;             
    char **args;        
    struct s_cmd *next; 
} t_cmd;



int	cd_var(char *var, t_env **env);
void	ft_echo(char **arg);
t_env ft_env(char **env, char **arg);
void	ft_exit(char **cmd);
t_env	ft_export(char **argv, char **env);
static void	process_heredocs(t_cmd *cmd, t_env *env);
void	ft_pwd(t_env *env);
void	ft_unset(t_env **env, t_cmd *cmd);

#endif