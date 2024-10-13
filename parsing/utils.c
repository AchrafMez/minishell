#include "minishell.h"

void print_list(t_command **command)
{
    t_command *cur = *command;
    while(cur)
    {
        printf("node->%s\n", cur->value);
        cur = cur->next;

    } 
}

void free_list(t_command **command)
{
    t_command *current = *command;
    t_command *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->value);
        free(current); 
        current = next;
    }

    *command = NULL;
}
t_command* init_node()
{
    t_command *new_node = malloc(sizeof(t_command));
    if(!new_node)
        return NULL;
    new_node->value = NULL;
    new_node->next = NULL;
    return new_node;
}

void add_node(t_command **command)
{
    t_command *new_node = init_node();
    if(!new_node)
    {
    // printf("here\n");

        return ;
    }
    else if(*command == NULL)
    {
        // printf("here1\n");
        (*command) = new_node;
    }
    else
    {
        // printf("here2\n");
        t_command *cur = (*command);
        while(cur->next != NULL)
            cur = cur->next;
        cur->next = new_node;
    }
}