/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:09:51 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 02:56:44 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	set_path(t_command **cmd)
{
	t_command	*cur;
	char		*path;

	path = NULL;
	cur = *cmd;
	while (cur)
	{
		if (cur->args && cur->args[0])
		{
			cur->name = ft_strdup(cur->args[0]);
			if (path != NULL)
			{
				cur->path = path;
				free(cur->args[0]);
				cur->args[0] = ft_strdup(cur->path);
			}
			else
				cur->path = ft_strdup(cur->args[0]);
		}
		cur = cur->next;
	}
}
