/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:25 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/16 12:55:45 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// int is_valid_key(char *arg)
// {
//     if(!*arg && (ft_isalpha(arg[0]) != 1) && arg[0] != '_')
//         return 1;
//     int i = 0;
//     while(arg[i])
//     {
//         if((ft_isalnum(arg[i]) != 1) && arg[i] != '_')
//             return 1;
//         i++;
//     }
//     return 0;
// }

void remove_keys(char *key, t_env **env)
{
    t_env *cur = *env;
    t_env *prev = NULL;
    while(cur)
    {
        if(ft_strcmp(cur->key, key) == 0)
        {
            printf("here\n");
            if(prev == NULL)
                *env = cur->next;
        else
            prev->next = cur->next;
        free(cur->key);
        free(cur->value);
        free(cur);
        printf("removed");
        return ;
        }
        prev = cur;
        cur = cur->next;
    }
}
int unset(char **args, t_env **env)
{
    if(!args[1])
    {
        printf("mimishell: unset: args not found\n");
        return 1;
    }
    int counter = 1;
    while(args[counter])
    {
        if(is_valid_key(args[counter]) == 1)
        {
            printf("%s nor a valid identifier\n", args[counter]);
            return 1;
        }    
        else{
            remove_keys(args[counter], env);
        }
        counter++;
    }
    return 0;
}
