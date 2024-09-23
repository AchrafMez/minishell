#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


//void simple_command(t_command *command)
//{
//	command->args = ft_taqsim(command->buf, ' ');
//	command->name = command->args[0];
//	printf("name:%s\n", command->name);
//	int i = 0;
//	while(command->args[i])
//	{
//		printf("arg:%s\n", command->args[i++]);
//	}
//}
//
////int check_pipes(char *buffer)
////{
////    int i = 0;
//////    int j = 0;
////    while(buffer[i])
////    {
////        if(buffer[i] == '|')
////        {
//////            j = i;
////            while(i >= 0)
////            {
////                if(buffer[i] == '"' || buffer[i] == '\'')
////                    return 1;
////                i--;
////            }
////        }
////        i++;
////    }
////
////}
//
//int ret_pipes(char *buffer)
//{
//    int count = 0;
//	while(*buffer)
//	{
//		if(*buffer == '|')
//		    count++;
//		buffer++;
//	}
//	return count;
//}
//
//void pipes_commands(t_command *command)
//{
//    command->npipes = ret_pipes(command->buf);
//    printf("pipes in buf: %d\n", command->npipes);
//    command->spipe = ft_taqsim(command->buf, '|');
//    int i = 0;
//    while(command->spipe[i])
//    {
//        printf("spipe: %s\n", command->spipe[i]);
//        i++;
//    }
//}
//
////void pipe_cmd(t_command *command)
////{
////
////}
//
//char ret_first_quote(char *buf)
//{
//    int i = 0;
//    while(buf[i]){
//        if(buf[i] == '"' || buf[i] == 39)
//            return buf[i];
//        i++;
//    }
//    return '\0';
//}
//
//int check_quote(char *buf)
//{
//    int single = 0;
//    int doub = 0;
//    int first = 0;
//    if(ret_first_quote(buf) == '\0')
//        return 3;
//    if(ret_first_quote(buf) == 39)
//        first = 1;
//    else if(ret_first_quote(buf) == '"')
//        first = 2;
//    while(*buf)
//    {
//        if(*buf == '"')
//            doub++;
//        else if(*buf == 39)
//            single++;
//        buf++;
//    }
//    if(first == 1 && (single % 2 == 0))
//        return 1;
//    else if(first == 2 && (doub % 2) == 0)
//        return 2;
//    return 0;
// }

// void init(t_command *command)
// {
//    int i = 0;
//
//    while(command->buf[i] != '\0')
//    {
//    }
//
// }


//void store_word(t_command *command, int *i)
//{
////    int start = *i;
//    int end = *i;
//    while((command->buf[*i] >= 'a' && command->buf[*i] <= 'z') || (command->buf[*i] >= 'A' && command->buf[*i] <= 'Z'))
//        end++;
//    command->value = ft_substr(command->buf, *i, end);
//}

int getwordlen(char *buf, int *j)
{
    int i = *j;
    while((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z'))
        i++;
    return i;
}

void handel_input(t_command *command)
{
    int index = 0;
//    int end = index;
    int i = 0;
    while(command->buf[i])
    {
        if(command->buf[index] == ' ' || command->buf[index] == '\t' || command->buf[index] == '\n' || command->buf[index] == '\v')
            index++;
        command->value = ft_substr(command->buf, index, getwordlen(command->buf, &index));
        i++;
    }
//    store_word(command, &index);
//    printf("%s\n", command->value);
}


int main(int ac, char **av, char **env) {
    t_command command;
    (void)av;
    (void)env;
    if(ac == 1)
    {
        while(1)
        {
            command.buf = readline("minishell> ");
            add_history(command.buf);
            handel_input(&command);
            printf("%s\n", command.value);
            free(command.buf);
        }
    }
    return 0;
}

//if(check_quote(command.buf) == 0)
//printf("\nQuotes Error\n\n");
//if(ret_pipes(command.buf) > 0)
//pipes_commands(&command);
//else
//simple_command(&command);