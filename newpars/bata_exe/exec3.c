/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/12/02 18:42:58 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/02 18:42:58 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**prc_allocation(int size)
{
	int	i;
	int	**tube;

	i = 0;
	tube = malloc(sizeof(int *) * size);
	if (!tube)
		return (NULL);
	while (i < size)
	{
		tube[i] = malloc(sizeof(int) * 2);
		if (!tube[i])
			return (NULL);
		i++;
	}
	return (tube);
}

void	check_o_pwd(char **str)
{
	if (ft_strcmp(str[0], "OLDPWD"))
	{
		free(str[1]);
		str[1] = ft_strdup("");
	}
}

t_env	*get_env(char **env)
{
	char		**str;
	int			i;
	t_env		*envp;
	t_env		*tmp;

	i = 0;
	str = NULL;
	envp = 0;
	while (env[i])
	{
		str = ft_strplit(env[i]);
		check_o_pwd(str);
		tmp = ft_lstnew_env(str[0], str[1]);
		if (ft_strcmp(tmp->key, "_"))
			tmp->dx = 0;
		else
			tmp->dx = 2;
		ft_lstadd_back_env(&envp, tmp);
		free(str);
		i++;
	}
	return (envp);
}

int	is_builting(t_command *cmd)
{
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		return (1);
	return (0);
}
