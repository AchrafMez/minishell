/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:21 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/27 16:07:28 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void print_export(t_env *env)
{
    t_env *cur = env;

    while(cur)
    {
        printf("dexlare -x %s=\"%s\"\n", cur->key, cur->value);
        cur = cur->next;
    }
}
t_env *find(t_env *env, char *key)
{
    while (env)
    {
        if(ft_strcmp(env->key, key) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}

int is_valid_key(char *arg)
{
    if(!*arg && (ft_isalpha(arg[0]) != 1) && arg[0] != '_')
    {
        printf("first char is incorrect\n");
        return 1;
    }
    int i = 0;
    while(arg[i])
    {
        if((ft_isalnum(arg[i]) != 1) && arg[i] != '_')
        {
            printf("incorrect key\n");
            return 1;
        }
        i++;
    }
    return 0;
}

void set_export_env(t_env **env, char *key, char *value)
{
    t_env *exist = find(*env, key);
    if(exist)
    {
        free(exist->value);
        exist->value = ft_strdup(value);
        return ;
    }
    else
    {
        t_env *new = malloc(sizeof(t_env));
        new->key = ft_strdup(key);
        new->value = ft_strdup(value);
        new->next = *env;
        *env = new;
    }
}

int export(char **args, t_env **env)
{
    if(!args[1] || ft_strcmp(args[1], "-p") == 0)
    {
        print_export(*env);
        return 0;
    }
    int counter = 1;
    while(args[counter])
    {
        char *arg = args[counter];
        char *sign = ft_strchr(arg, '=');
        if(sign)
        {
            *sign = '\0';
            char *key = arg;
            printf("key: %s\n", key);
            if(is_valid_key(key) == 1)
            {
                printf("minishell: export: '%s': not a valid edentifier\n", args[1]);
                return 1;
            }
            char *value = sign+1;
            set_export_env(env, key, value);
        }
        else
            set_export_env(env, arg, "");
        counter++;
    }
    return 0;
}
