/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:44:06 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/03 05:15:51 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_the_head(t_env *tmp, t_env *before, char **unset, t_env **env)
{
	if (ft_strcmp(tmp->key, *unset))
	{
		before = tmp->next;
		env_del(tmp);
		*env = before;
		return (0);
	}
	return (1);
}

void	unset_arguments(t_env **env, char **unset)
{
	t_env	*tmp;
	t_env	*before;

	before = NULL;
	tmp = *env;
	if (!unset_the_head(tmp, before, unset, env))
		return ;
	while (tmp)
	{
		if (tmp->next && !ft_strcmp(tmp->next->key, *unset))
		{
			before = tmp->next->next;
			env_del(tmp->next);
			tmp->next = before;
		}
		else if (!ft_strcmp(tmp->key, *unset))
		{
			env_del(tmp);
			*env = 0;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_env **env, char **unset)
{
	g_glb.ex = 0;
	unset++;
	if (!env)
	{
		g_glb.ex = 1;
		return ;
	}
	while (*unset)
	{
		if (!condition_name(*unset))
			export_error(*unset);
		unset_arguments(env, unset);
		unset++;
	}
}
