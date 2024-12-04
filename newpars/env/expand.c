/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 02:28:59 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 02:29:10 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *searsh)
{
	t_env	*temp;

	temp = env;
	if (!searsh || *searsh == '\0')
		return ("");
	while (temp && temp != NULL)
	{
		if (searsh == NULL || temp->key == NULL)
			return ("");
		if (!ft_strcmp(temp->key, searsh))
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}
