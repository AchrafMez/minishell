#include "minishell.h"

void ft_free_env(t_env *env)
{
    t_env *tmp = env;
    t_env *next;
    while(tmp)
    {
        next = tmp->next;
        free(tmp->value);
        free(tmp);
        tmp = next;
    }
}

void display_env(t_env *temp)
{
    t_env *tmp = temp;
    while(tmp)
    {
        printf("key -> %s\n", tmp->key);
        printf("value -> %s\n", tmp->value);
        printf("--------------------------------------\n");
        tmp = tmp->next;
    }
}

void dup_env(char **envp, t_env **env)
{
    *env = malloc(sizeof(t_env));
    t_env *tmp = *env;
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
        tmp->key = ft_substr(envp[i], 0, j);
        tmp->value = ft_substr(envp[i], j + 1, strlen(envp[i]));
        j = 0;
        i++;
        if(envp[i + 1] != NULL)
        {
            tmp->next = malloc(sizeof(t_env));
            tmp = tmp->next;
        } else
            tmp->next = NULL;
    }
//    display_env(*env);
}

