/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:18 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/16 12:15:19 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

