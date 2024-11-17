/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:16 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/17 11:30:02 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(char **args)
{
    int counter;
    int n_flag = 0;
    // printf("here\n");

    counter = 1;
    if(args[counter] && ft_strcmp(args[counter], "-n") == 0)
    {
        counter++;
        n_flag = 1;
    }
    // printf("here1\n");
    while(args[counter])
    {
        // printf("here2\n");
        printf("%s", args[counter]);
        if(args[counter + 1] != NULL)
            printf(" ");
        counter++;
    }
    if(n_flag == 0)
        printf("\n");
    return 0;
}


