/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:42:40 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/05 07:49:02 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_wait(t_extra ptr, t_env **env)
{
	int	i;
	int	status;
	int	res;

	free_tab(ptr.path);
	free_tab(ptr.envp);
	closingb(ptr.tube, ptr.size);
	i = 0;
	while (i <= ptr.size)
	{
		waitpid(ptr.pid[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			res = 128 + WEXITSTATUS(status);
			update_exit_value(env, res);
			// set_export_env(env, "?", ft_itoa(res));
		}
		else
		{
			res = WEXITSTATUS(status);
			update_exit_value(env, res);
			// set_export_env(env, "?", ft_itoa(res));
		}
		i++;
	}
	free(ptr.pid);
}
