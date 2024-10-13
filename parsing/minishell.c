#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

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



int getwordlen(char *buf, int i)
{
    int len = 0;
    while(buf[i + len] != ' ' && ((buf[i + len] >= 'a' && buf[i + len] <= 'z') || (buf[i + len] >= 'A' && buf[i + len] <= 'Z') || (buf[i + len] >= '0' && buf[i + len] <= '9')))
        len++;
    return len;
}


int is_space(t_command *command)
{
    int i = 0;
    while(command->buf[i] != '0')
    {
        if(command->buf[i] == ' ' || command->buf[i] == '\t' || command->buf[i] == '\v' || command->buf[i] == '\n')
            return 1;
        i++;
    }
    return 0;
}
t_command *ret_last(t_command **command)
{
    t_command *temp = *command;
    while(temp->next != NULL)
        temp = temp->next;
    return temp;
}
void full_word(t_command **command, char *buf, int *index)
{
    int start = *index;
    t_command *cur = ret_last(command);
    while(((buf[(*index)] >= 'a' && buf[*index] <= 'z') || (buf[*index] >= 'A' && buf[*index] <= 'Z') || (buf[*index] >= '0' && buf[*index] <= '9')))
        (*index)++;
    int end = *index - start;
    cur->value = ft_substr(buf, start, end);
    // printf("command value -> %s\n", (*command)->value);

}


void full_spaces(t_command **command, char *buf, int *index)
{
//    while((*command)->buf[(*command)->index] == ' ' || (*command)->buf[(*command)->index] == '\t' || (*command)->buf[(*command)->index] == '\v' || (*command)->buf[(*command)->index] == '\n')
//    {
    t_command *cur = ret_last(command);
       if(buf[(*index)] == ' ')
           cur->value = ft_strdup(" ");
    //    else if(buf[(*index)] == '\t')
        //    cur->value = ft_strdup("\t.tab");
    //    else if(buf[(*index)] == '\n')
    //        cur->value = ft_strdup("\n");
    //    else if(buf[(*index)] == '\v')
    //        cur->value = ft_strdup("\v");
       // (*command)->next = NULL;
//        (*command)->index++;
//    }
}
void full_specail(t_command **command, char *buf, int *index)	
{
    t_command *cur = ret_last(command);
    if(buf[(*index)] == '\'')
        cur->value = ft_strdup("'");
    if(buf[(*index)] == '\"')
        cur->value = ft_strdup("\"");
    if(buf[(*index)] == '<')
        cur->value = ft_strdup("<");
    if(buf[(*index)] == '>')
        cur->value = ft_strdup(">");
    if(buf[(*index)] == '|')
        cur->value = ft_strdup("|");
    if(buf[(*index)] == '.')
        cur->value = ft_strdup(".");
    if(buf[(*index)] == '-')
        cur->value = ft_strdup("-");
    if(buf[(*index)] == '_')
        cur->value = ft_strdup("_");
    if(buf[(*index)] == '$')
        cur->value = ft_strdup("$");
    
}

char* check_quote_type(char *str)
{
    if(!strcmp(str, "'") || !strcmp(str, "\""))
        return str;
    return NULL;
}

char *handle_quotes(t_command **command, char *buf)
{
    t_command *cur = *command;
    char *quote_type = check_quote_type(cur->value);
    cur = cur->next;
    while(cur && strcmp(cur->value, quote_type))
    {
        buf = ft_strjoin(buf, cur->value);
        cur = cur->next;
    }
    *command = cur;
    if (!cur)
        return NULL;
    return buf;
}
void print_cmd(t_cmd *cmd_list)
{
    t_cmd *cur_cmd = cmd_list;
    int i;

    // while (cur_cmd)
    // {
        printf("Command:\n");
        i = 0;
        while (cur_cmd->av[i])
        {
            printf("  av[%d]: %s\n", i, cur_cmd->av[i]);
            i++;
        }
        // cur_cmd = cur_cmd->next;
        // if (cur_cmd)
        //     printf("Next command:\n");
    // }
}

t_cmd **check_quotes(t_command **command, t_cmd **cmd)
{
    t_command *cur = *command;
    char *ret = "";
    int i = 0;

    // Allocate memory for cmd if it is NULL
    if (*cmd == NULL) {
        *cmd = malloc(sizeof(t_cmd));
        (*cmd)->av = malloc(sizeof(char*) * 10);
        memset((*cmd)->av, 0, sizeof(char*) * 10);
    }

    while (cur)
    {
        if (!strcmp(cur->value, " "))
        {
            cur = cur->next;
            continue;
        }
        else if (check_quote_type(cur->value))
        {
            ret = handle_quotes(&cur, ret);
            if (!ret) {
                printf("unclosed quote?\n");
            }
            if ((cur && !cur->next) || (cur && cur->next && !strcmp(cur->next->value, " ")))
            {
                (*cmd)->av[i++] = ret;
                ret = "";
            }
        }
        else if (!strcmp(cur->value, "|")) {
            return cmd;
        }
        else {
            (*cmd)->av[i] = cur->value;
            i++;
        }
        if (cur)
            cur = cur->next;
    }
    return cmd;
}
// t_cmd **check_quotes(t_command **command, t_cmd **cmd)
// {
//     t_command *cur = *command;
//     char *ret = "";
//     char **argv = malloc(sizeof(char*) * 10);
//     memset(argv, 0, sizeof(char*) * 10);
//     int  i = 0;
//     while(cur)
//     {
//         if(!strcmp(cur->value, " "))
//         {
//             cur = cur->next;
//             continue;
//         }
//         else if(check_quote_type(cur->value))
//         {
//             ret = handle_quotes(&cur, ret);
//             if (!ret) {
//                 printf("unclosed quote?\n");
//             }
//             if((cur && !cur->next) || (cur && cur->next && !strcmp(cur->next->value, " ")))
//             {
//                 argv[i++] = ret;
//                 ret = "";
//             }
//         }
//         else if(!strcmp(cur->value, "|")) {
//             return argv;
//         }
//         else {
//             argv[i] = cur->value;
//             i++;
//         }
//         if (cur)
//             cur = cur->next;
//     }
//     return argv;
// }

void print_av(char **av)
{
    int i = 0;
    while(av[i])
    {
        printf("av %d: %s\n", i, av[i]);
        i++;
    }
}

t_command **check_type(char *buf, t_command **command)
{
    int index = 0;
    while(buf[index] != '\0')
    {
        if(((buf[index] >= 'a' && buf[index] <= 'z') || (buf[index] >= 'A' && buf[index] <= 'Z') || (buf[index] >= '0' && buf[index] <= '9')))
        {
            add_node(command);
            full_word(command, buf, &index);
        }
       if(buf[index] == ' ' || buf[index] == '\t' || buf[index] == '\v' || buf[index] == '\n')
       {
            add_node(command);
           full_spaces(command, buf, &index);
       }

       else if(buf[index] == '\"' || buf[index] == '\'' || buf[index] == '.' || buf[index] == '<' || buf[index] == '>' || buf[index] == '|' || buf[index] == '-' || buf[index] == '_' || buf[index] == '$')
       {
            add_node(command);
            full_specail(command, buf, &index);
       }
        index++;
        // printf("idx in check type -> %d \n", index);
    }
    return command;
}

char *skip_spaces(char *buf)
{
    if(!buf)
        return NULL;
    int i = 0;
    while(buf[i] && (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n' || buf[i] == '\v'))
        i++;
    return ft_substr(buf, i, ft_strlen(buf));
}

void free_cmd_list(t_cmd *cmd_list)
{
    t_cmd *cur_cmd = cmd_list;
    // t_cmd *next_cmd;

    // while (cur_cmd)
    // {
        // next_cmd = cur_cmd->next;
        if (cur_cmd->av)
        {
            for (int i = 0; cur_cmd->av[i]; i++)
            {
                free(cur_cmd->av[i]);
            }
            // free(cur_cmd->av);
        }
        // free(cur_cmd);
        // cur_cmd = next_cmd;
    // }
}

void handel_input(void)
{
    char *temp;
    t_command *command = NULL;
    t_cmd *cmd = NULL;
    // malloc(sizeof(t_command));
    while(1)
    {
        temp = readline("minishell> ");
        add_history(temp);
        check_type(skip_spaces(temp), &command);
        check_quotes(&command, &cmd);
        print_cmd(cmd);
        // free_cmd_list(cmd);
        // print_av(ret);
        free(temp);
        // print_list(&command);
        free_list(&command);
    }
}

int main(int ac, char **av, char **envp){
    (void)av;
    (void)envp;
    //  t_env *env = malloc(sizeof(t_env));
    //  get_env(envp, &env);
     if(ac == 1)
         handel_input();
    return 0;
}