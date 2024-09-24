#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"

typedef struct red{
    int type;
    char *file;
} red;

typedef struct test {
    char * command;
    char **args ;
    red *redir;
    struct test *next;

} test;

typedef struct s_env{
    char *key;
     char *value;
     struct s_env *next;
} t_env;

//typedef struct z_command
//{
//    char *buf; //buffer for reading the input
//    char *value;
//
//    int npipes;
//    char **spipe;
//    char *name; //comand name
//    char **args; //command arguments
//    struct s_command *next; //next command
//
//} l_command;

typedef struct s_token
{
    enum {
        TOKEN_WHITESPACES,
        TOKEN_SEMICOLON,
        NEWLINE,
        BACK_SLASH,
        SINGLE_QUOTE,
        DOUBLE_QUOTE,

    } e_type;
    char			*value; //token itself (;, word or string)
    int				order;  //serves to have position of the token in the input
}					t_token;


typedef struct s_command
{
    char *buf;
    char *value;
    char **check;
    struct s_command *next;
} t_command;

char	**ft_taqsim(char *s, char c);
void get_env(char **envp, t_env **env);


#endif