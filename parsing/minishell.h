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

typedef struct s_command
{
    char *buf;
    char *value;
    char **check;
    struct s_command *next;
} t_command;

char	**ft_taqsim(char *s, char c);

#endif