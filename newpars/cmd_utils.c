#include "minishell.h"

t_command* init_node(int args_size)
{
    t_command *new_node = malloc(sizeof(t_command));
    if(!new_node)
        return NULL;
    new_node->args = NULL;
    new_node->next = NULL;
    return new_node;
}

void add_node(t_command **command, int args_size)
{
    t_command *new_node = init_node(args_size);
    if(!new_node)
        return ;
    else if(*command == NULL)
        (*command) = new_node;
    else
    {
        t_command *cur = (*command);
        while(cur->next != NULL)
            cur = cur->next;
        cur->next = new_node;
    }
}