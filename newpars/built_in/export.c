/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:21 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 03:03:52 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	is_valid_key(char *arg)
{
	int	i;

	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i])
	{
		if ((!ft_isalnum(arg[i])) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	set_export_env(t_env **env, char *key, char *value)
{
	t_env	*exist;
	t_env	*new;

	exist = find(*env, key);
	if (exist)
	{
		free(exist->value);
		exist->value = ft_strdup(value);
		return ;
	}
	else
	{
		new = malloc(sizeof(t_env));
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->next = *env;
		*env = new;
	}
}

int	process_export_arg(char *arg, t_env **env)
{
	char	*sign;
	char	*key;
	char	*value;

	sign = ft_strchr(arg, '=');
	if (sign)
	{
		*sign = '\0';
		key = arg;
		value = sign + 1;
		if (!is_valid_key(key))
			return (1);
		set_export_env(env, key, value);
	}
	else
	{
		if (!is_valid_key(arg))
			return (1);
		set_export_env(env, arg, "");
	}
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	int	counter;

	if (!args[1])
	{
		print_export(*env);
		return (0);
	}
	counter = 1;
	while (args[counter])
	{
		if (process_export_arg(args[counter], env) != 0)
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				args[counter]);
			return (1);
		}
		counter++;
	}
	return (0);
}
