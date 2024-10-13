#include "minishell.h"

//void display_env(t_env *tmp)
//{
//    while(tmp)
//    {
//        printf("key -> %s\n", tmp->key);
//        printf("value -> %s\n", tmp->value);
//        printf("--------------------------------------\n");
//        tmp = tmp->next;
//    }
//}

void get_env(char **envp, t_env **env)
{
//    env = malloc(sizeof(t_env));
    // t_env *tmp;
    // tmp = *env;
    int i = 0;
    int j = 0;
    while(envp[i])
    {
        while(envp[i][j])
        {
            if(envp[i][j] == '=')
                break ;
            j++;
        }
        (*env)->key = ft_substr(envp[i], 0, j);
        (*env)->value = ft_substr(envp[i], j + 1, strlen(envp[i]));
        j = 0;
        i++;
        if(envp[i + 1] != NULL)
        {
            (*env)->next = malloc(sizeof(t_env));
            *env = (*env)->next;
        } else
            (*env)->next = NULL;
    }
//    display_env(&*tmp);
}

