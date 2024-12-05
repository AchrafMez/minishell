/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:16 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 02:50:04 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n_flag(char *tab)
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
	if (!arg[1])
	{
		printf("\n");
		return (1);
	}
	if (check_n_flag(arg[1]))
		n_flag = 1;
	else
		n_flag = 0;
	if (n_flag)
		i++;
	print_arguments(&arg[i]);
	if (!n_flag)
		printf("\n");
	return (0);
}
