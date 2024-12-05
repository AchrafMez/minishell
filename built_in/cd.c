/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:13 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 03:02:24 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd_get_target(char **args, t_env *env)
{
	char	*target;

	if (!args[1])
	{
		target = get_env_value(env, "HOME");
		if (!target)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else
	{
		target = args[1];
	}
	return (target);
}

int	cd_change_directory(char *target, t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	set_env_value(&env, "OLDPWD", cwd);
	free(cwd);
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	return (cd_update_environment(env));
}

int	cd_update_environment(t_env *env)
{
	char	*new;

	new = getcwd(NULL, 0);
	if (new)
	{
		set_env_value(&env, "PWD", new);
		free(new);
	}
	else
	{
		perror("cd: getcwd");
		return (1);
	}
	return (0);
}

int	cd(char **args, t_env *env)
{
	char	*target;

	target = cd_get_target(args, env);
	if (!target)
		return (1);
	return (cd_change_directory(target, env));
}
