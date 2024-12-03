/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:43:11 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/03 05:13:54 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_echo(char **arg)
{
	int	i;
	int	n_flag;

	i = 1;
	g_glb.ex = 0;
	if (!arg[1])
	{
		printf("\n");
		return ;
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
}
