#include "../minishell.h"

void print_cmd(t_command *command)
{
    t_command *cur = command;
    while(cur)
    {
        int i = 0;
        printf("cmd path: %s\n", cur->path);
        while(cur->args[i])
        {
            printf("arg: %s\n", cur->args[i]);
            i++;
        }
        t_red *tmp = cur->in;
        t_red *out_tm = cur->out;
        while(out_tm)
        {
            printf("ouput file: %s typt: %u\n", out_tm->value, out_tm->type);
            out_tm = out_tm->next;
        }
        while(tmp)
        {
            printf("input file: %s typt: %u\n", tmp->value, tmp->type);
            tmp = tmp->next;
        }
        printf("------- another cmd -------\n");
        cur = cur->next;
    }
}

void free_cmd(t_command *command)
{
    t_command *cur = command;
    t_command *next ;
    while(cur)
    {
        next = cur->next;
        int i = 0;
        while(cur->args[i])
        {
            free(cur->args[i]);
            i++;
        }
        free(cur->args);
        free(cur->path);
        t_red *red_tmp = cur->in;
        while(red_tmp)
        {
            t_red *next_red = red_tmp->next;
            free(red_tmp->value);
            free(red_tmp);
            red_tmp = next_red;
        }
        t_red *red_out = cur->out;
        while(red_out)
        {
            t_red *next_out = red_out->next;
            free(red_out->value);
            free(red_out);
            red_out = next_out;
        }
        free(cur);
        cur = next;
    }
}
