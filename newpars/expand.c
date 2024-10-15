#include "minishell.h"

char *get_env_value(t_env *env, char *searsh)
{
    t_env *temp = env;
    if(!searsh || *searsh == '\0')
        return "";
    while(temp && temp != NULL)
    {
        if(searsh  == NULL || temp->key == NULL)
                return "";
        if(!strcmp(temp->key, searsh))
            return temp->value;
        temp = temp->next;
    }
    return "";
}