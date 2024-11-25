/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:09:51 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/25 10:34:06 by abattagi         ###   ########.fr       */
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

char	*get_path(char *target)
{
	char	*env_path;
	char	**path;
	int		i;
	char	*slash_dir;
	char	*full_path;

	env_path = getenv("PATH");
	if (!env_path)
		return (NULL);
	path = ft_split(env_path, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		slash_dir = ft_strjoin(path[i], "/");
		if (!slash_dir)
		{
			free_path(path);
			return (NULL);
		}
		full_path = ft_strjoin(slash_dir, target);
		free(slash_dir);
		if (!full_path)
		{
			free_path(path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_path(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_path(path);
	return (NULL);
}

void	set_path(t_command **cmd)
{
	t_command	*cur;
	char		*path  = NULL;

	cur = *cmd;
	while (cur)
	{
		if (cur->args && cur->args[0])
		{
			cur->name = ft_strdup(cur->args[0]);
			// path = allocptr(&ptr, &tmp, env);
			if (path != NULL)
			{
				cur->path = path;
				free(cur->args[0]);
				cur->args[0] = ft_strdup(cur->path);
			}
			else
			{
				cur->path = ft_strdup(cur->args[0]);
			}
		}
		cur = cur->next;
	}
}
