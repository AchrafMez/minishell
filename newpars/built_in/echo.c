/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:16 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 00:18:56 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int echo(char **args)
// {
//     int counter;
//     int n_flag = 0;
//     // printf("here\n");

//     counter = 1;
//     if(args[counter] && ft_strcmp(args[counter], "-n") == 0)
//     {
//         counter++;
//         n_flag = 1;
//     }
//     // printf("here1\n");
//     while(args[counter])
//     {
//         // printf("here2\n");
//         printf("%s", args[counter]);
//         if(args[counter + 1] != NULL)
//             printf(" ");
//         counter++;
//     }
//     if(n_flag == 0)
//         printf("\n");
//     return 0;
// }
int	check_n_Flag(char *tab)
{
	if (*tab != '-')
		return (0);
	tab++;
	while (*tab)
	{
		if (*tab != 'n')
			return (0);
		tab++;
	}
	return (1);
}

void	print_arguments(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i + 1])
			printf("%s ", arg[i]);
		else
			printf("%s", arg[i]);
		i++;
	}
}

int	ft_echo(char **arg)
{
	int	i;
	int	n_flag;

	i = 1;
	// g_glb.ex = 0;
	if (!arg[1])
	{
		printf("\n");
		return(1) ;
	}
	if (check_n_Flag(arg[1]))
		n_flag = 1;
	else
		n_flag = 0;
	if (n_flag)
		i++;
	print_arguments(&arg[i]);
	if (!n_flag)
		printf("\n");
        return 0;
}

