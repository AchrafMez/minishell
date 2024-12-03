/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:44:01 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/02 18:44:02 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_env *env)
{
	char	*p;
	t_env	*tmp;

	tmp = env;
	p = getcwd(NULL, 0);
	if (p)
	{
		printf("%s\n", p);
		free(p);
	}
	else
	{
		while (tmp)
		{
			if (strcmp(tmp->key, "PWD"))
			{
				printf("%s\n", tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
	}
}
