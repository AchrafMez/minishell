/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:18 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 02:50:55 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_error(char *c)
{
	write(2, "env: ", 5);
	write(2, c, ft_strlen(c));
	write(2, ": No such file or directory\n", 28);
}

int	ft_enva(t_env **env, char **arg)
{
	t_env	*tmp;

	tmp = *env;
	if (!get_envarement(env, "PATH"))
	{
		write(2, "env: No such file or directory\n", 31);
		return (1);
	}
	if (arg[1])
	{
		print_env_error(arg[1]);
		return (127);
	}
	while (tmp)
	{
		if (tmp->dx == 0 || tmp->dx == 2)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
