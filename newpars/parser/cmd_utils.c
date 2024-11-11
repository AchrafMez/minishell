#include "../minishell.h"

void add_red(t_red **red_list, char *value, t_token_type type)
{
    t_red *new_red = malloc(sizeof(t_red));
    new_red->value = strdup(value);
    new_red->type = type;
    new_red->next = NULL;

    if (*red_list == NULL) {
        *red_list = new_red;
        return;
    }

    t_red *cur = *red_list;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = new_red;
}

void add_arg(char ***args, int *arg_count, char *value)
{
    int count = 0;
    while ((*args)[count]) count++;
    
    char **new_args = malloc(sizeof(char *) * (count + 2));
    for (int i = 0; i < count; i++) {
        new_args[i] = (*args)[i];
    }
    new_args[count] = strdup(value);
    new_args[count + 1] = NULL;

    free(*args);
    *args = new_args;
    (*arg_count)++;
}

t_command *create_command()
{
    t_command *cmd = malloc(sizeof(t_command));
    cmd->args = malloc(sizeof(char *));
    cmd->args[0] = NULL;
    cmd->path = NULL;
    cmd->in = NULL;
    cmd->out = NULL;
    cmd->next = NULL;
    return cmd;
}
