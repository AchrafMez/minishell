#include "../minishell.h"

void set_env_value(t_env **env, char *searsh, char *set)
{
    t_env *cur = *env;
    while(cur)
    {
        if(ft_strcmp(cur->key, searsh) == 0)
        {
            free(cur->value);
            cur->value = ft_strdup(set);
            printf("%s cur.value\n\n\n", cur->value);
            return ;
        }
        cur = cur->next;
    }
}