#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "/home/captain/Desktop/mysh/libft/libft.h"

typedef struct s_command
{
    char *buf; //buffer for reading the input
    char *name; //comand name
    char **args; //command arguments
    struct s_command *next; //next command
    
} t_command;

#endif