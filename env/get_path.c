/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 02:55:34 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 03:03:19 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_path(char *dir, char *target)
{
	char	*slash_dir;
	char	*full_path;

	slash_dir = ft_strjoin(dir, "/");
	if (!slash_dir)
		return (NULL);
	full_path = ft_strjoin(slash_dir, target);
	free(slash_dir);
	return (full_path);
}

int	check_access(char *full_path)
{
	if (access(full_path, X_OK) == 0)
		return (1);
	return (0);
}

char	**get_env_path(void)
{
	char	*env_path;

	env_path = getenv("PATH");
	if (!env_path)
		return (NULL);
	return (ft_split(env_path, ':'));
}

char	*find_exec(char **path, char *target)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path[i])
	{
		full_path = join_path(path[i], target);
		if (!full_path)
		{
			free_path(path);
			return (NULL);
		}
		if (check_access(full_path))
		{
			free_path(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *target)
{
	char	**path;
	char	*executable_path;

	path = get_env_path();
	if (!path)
		return (NULL);
	executable_path = find_exec(path, target);
	free_path(path);
	return (executable_path);
}
