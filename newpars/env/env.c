/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:15:18 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/13 10:15:19 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
		tmp = next;
	}
}

void	display_env(t_env *temp)
{
	t_env	*tmp;

	tmp = temp;
	while (tmp)
	{
		printf("key -> %s\n", tmp->key);
		printf("value -> %s\n", tmp->value);
		printf("--------------------------------------\n");
		tmp = tmp->next;
	}
}

void	dup_env(char **envp, t_env **env)
{
	t_env	*tmp;
	int		i;
	int		j;
	t_env	*new;

	*env = NULL;
	tmp = NULL;
	i = 0;
	j = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
				break ;
			j++;
		}
		new->key = ft_substr(envp[i], 0, j);
		new->value = ft_substr(envp[i], j + 1, strlen(envp[i]));
		new->next = NULL;
		if (*env == NULL)
			*env = new;
		else
			tmp->next = new;
		tmp = new;
		j = 0;
		i++;
	}
	//    display_env(*env);
}
