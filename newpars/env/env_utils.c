/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:15:18 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/27 17:04:34 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_free_env(t_env **env)
// {
// 	t_env	*tmp;
// 	t_env	*next;

// 	tmp = *env;
// 	while (tmp)
// 	{
// 		next = tmp->next;
// 		free(tmp->value);
// 		free(tmp->key);
// 		free(tmp);
// 		tmp = next;
// 	}
// }

// void	display_env(t_env *temp)
// {
// 	t_env	*tmp;

// 	tmp = temp;
// 	while (tmp)
// 	{
// 		printf("key -> %s\n", tmp->key);
// 		printf("value -> %s\n", tmp->value);
// 		printf("--------------------------------------\n");
// 		tmp = tmp->next;
// 	}
// }

// void	dup_env(char **envp, t_env **env)
// {
// 	t_env	*tmp;
// 	int		i;
// 	int		j;
// 	t_env	*new;

// 	*env = NULL;
// 	tmp = NULL;
// 	i = 0;
// 	j = 0;
// 	while (envp[i])
// 	{
// 		new = malloc(sizeof(t_env));
// 		while (envp[i][j])
// 		{
// 			if (envp[i][j] == '=')
// 				break ;
// 			j++;
// 		}
// 		new->key = ft_substr(envp[i], 0, j);
// 		new->value = ft_substr(envp[i], j + 1, strlen(envp[i]));
// 		new->next = NULL;
// 		if (*env == NULL)
// 			*env = new;
// 		else
// 			tmp->next = new;
// 		tmp = new;
// 		j = 0;
// 		i++;
// 	}
// 	//    display_env(*env);
// }
char	**ft_spliiit(char *env)
{
	int		i;
	char	**str;
	int		len;

	str = NULL;
	i = -1;
	len = ft_strlen(env);
	while (env[++i] && env[i] != '=')
		;
	str = malloc(sizeof(char *) * 3);
	str[0] = ft_substr(&env[0], 0, i);
	if (!env[i])
		str[1] = ft_strdup("");
	else
		str[1] = ft_substr(&env[i], 1, len);
	str[2] = 0;
	return (str);
}
int	ft_cmp(const char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s1[i])
		return (1);
	return (0);
}
void	old_pwd_check(char **str)
{
	if (ft_cmp(str[0], "OLDPWD"))
	{
		free(str[1]);
		str[1] = ft_strdup("");
	}
}

t_env	*convert_env(char **env)
{
	char	**str;
	int		i;
	t_env	*envp;
	t_env	*tmp;

	i = 0;
	str = NULL;
	envp = 0;
	while (env[i])
	{
		str = ft_spliiit(env[i]);
		old_pwd_check(str);
		tmp = ft_lstnew_env(str[0], str[1]);
		if (ft_cmp(tmp->key, "_"))
			tmp->dx = 0;
		else
			tmp->dx = 2;
		ft_lstadd_back_env(&envp, tmp);
		free(str);
		i++;
	}
	return (envp);
}
