/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 02:38:41 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 02:38:49 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_env_value(t_env **env, char *searsh, char *set)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, searsh) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(set);
			return ;
		}
		cur = cur->next;
	}
}
