/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:21 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/01 05:32:44 by amezioun         ###   ########.fr       */
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
    if(!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
        return 0;
    int i = 1;
    while(arg[i])
    {
        if((!ft_isalnum(arg[i])) && arg[i] != '_')
            return 0;
        i++;
    }
    return 1;
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

int process_export_arg(char *arg, t_env **env)
{
    char *sign;
    
    sign = ft_strchr(arg, '=');
    if (sign)
    {
        *sign = '\0';
        char *key = arg;
        char *value = sign + 1;
        if (!is_valid_key(key))
            return 1;
        set_export_env(env, key, value);
    }
    else
    {
        if (!is_valid_key(arg))
            return 1;
        set_export_env(env, arg, "");
    }
    return 0;
}

int export(char **args, t_env **env)
{
    if (!args[1])
    {
        print_export(*env);
        return 0;
    }

    int counter = 1;
    while (args[counter])
    {
        if (process_export_arg(args[counter], env) != 0)
        {
            printf("minishell: export: `%s': not a valid identifier\n", args[counter]);
            return 1;
        }
        counter++;
    }
    return 0;
}
