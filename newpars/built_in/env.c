#include "../minishell.h"

int ft_env(char **args, t_env *env)
{
    t_env *cur = env;
    if(args[1])
    {
        printf("env: too many argumets\n");
        return 1;
    }
    else
    {
        while(cur)
        {
            printf("%s=%s\n", cur->key, cur->value);
            cur = cur->next;
        }
        return 0;
    }
}

