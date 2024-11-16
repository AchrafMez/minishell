/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:08 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/16 15:19:10 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exit(char **args, int last_e_s)
{
    // int exit_s = 0;
    int i = 0;
    if(args[0] && args[1] && args[2])
    {
        printf("minishell: exit: too many arguments\n");
        return 2;
    }
    if(args[1])
    {
        while(args[i])
        {
            if(!(args[1][i] >= '0' && args[1][i] <= '9'))
            {
                printf("exit\nminishell: exit: %s numeric argument required\n", args[1]);
                exit(2);
            }
            i++;
        }
        // printf("exit :%d\n", exit_s);
        exit(ft_atoi(args[1]));
    }
    exit(last_e_s);
}