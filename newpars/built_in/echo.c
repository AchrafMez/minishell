/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:16 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/16 12:15:17 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(char **args)
{
    int counter;
    int n_flag = 0;

    counter = 1;
    if(ft_strcmp(args[counter], "-n") == 0)
    {
        counter++;
        n_flag = 1;
    }
    while(args[counter])
    {
        printf("%s", args[counter]);
        if(args[counter + 1] != NULL)
            printf(" ");
        counter++;
    }
    if(n_flag != 1)
        printf("\n");
    return 0;
}

