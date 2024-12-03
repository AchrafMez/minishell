/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: captain <captain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:42:40 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/03 23:16:45 by captain          ###   ########.fr       */
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

	free_tab(ptr.path);
	free_tab(ptr.envp);
	closingb(ptr.tube, ptr.size);
	i = 0;
	while (i <= ptr.size)
	{
		waitpid(ptr.pid[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			int res =  128 + WEXITSTATUS(status);
			set_export_env(env, "?", ft_itoa(res));
			// printf("exit status: %d\n", res);
		}
		else
		{
			int res = WEXITSTATUS(status);
			set_export_env(env, "?", ft_itoa(res));	
			// printf("exit status: %d\n", res); 
		}
		i++;
	}
	free(ptr.pid);
}
