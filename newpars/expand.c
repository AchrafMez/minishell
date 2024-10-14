#include "minishell.h"

char *get_env_value(t_env *env, char *searsh)
{
    t_env *temp = env;
    while(temp)
    {
        if(!strcmp(temp->key, searsh))
            return temp->value;
        temp = temp->next;
    }
    return NULL;
}