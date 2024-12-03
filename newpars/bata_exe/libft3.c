/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/12/02 18:44:37 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/02 18:44:37 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	if (!*lst)
	{
		ft_lstadd_front_env(lst, new);
		return ;
	}
	ft_lstlast_env(*lst)->next = new;
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env *lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = key;
	lst->value = value;
	lst->next = NULL;
	return (lst);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *ptr_d;
	char *ptr_s;

	i = 0;
	ptr_d = (char *)dest;
	ptr_s = (char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*ptr_d++ = *ptr_s++;
		i++;
	}
	return (dest);
}

char	**ft_strplit(char *env)
{
	int i;
	char **str;
	int len;

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

void	export_error(char *exp)
{
	write(2, "export : ", 9);
	write(2, exp, ft_strlen(exp));
	write(2, " : not a valid identifier\n", 26);
	g_glb.ex = 1;
}
