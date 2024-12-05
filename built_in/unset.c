/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:25 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/05 07:01:00 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_keys(char *key, t_env **env)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev == NULL)
				*env = cur->next;
			else
				prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	unset(char **args, t_env **env)
{
	int	counter;

	if (!args[1])
	{
		printf("mimishell: unset: args not found\n");
		return (1);
	}
	counter = 1;
	while (args[counter])
	{
		if (!is_valid_key(args[counter]))
		{
			printf("%s nor a valid identifier\n", args[counter]);
			return (1);
		}
		else
			remove_keys(args[counter], env);
		counter++;
	}
	return (0);
}
