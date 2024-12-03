/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: captain <captain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:18 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/03 23:15:51 by captain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int ft_env(char **args, t_env *env)
// {
//     t_env *cur = env;
//     if(args[1])
//     {
//         printf("env: too many argumets\n");
//         return 1;
//     }
//     else
//     {
//         while(cur)
//         {
//             printf("%s=%s\n", cur->key, cur->value);
//             cur = cur->next;
//         }
//         return 0;
//     }
// }
#include "../minishell.h"

void	print_env_error(char *c)
{
	write(2, "env: ", 5);
	write(2, c, ft_strlen(c));
	write(2, ": No such file or directory\n", 28);
}

int	ft_enva(t_env **env, char **arg)
{
	t_env	*tmp;

	tmp = *env;
	// printf("==>>>>>>>>>>>>>>>>%s=%s\n", tmp->key, tmp->value);
	if (!get_envarement(env, "PATH"))
	{
		write(2, "env: No such file or directory\n", 31);
		return 1;
	}
	if (arg[1])
	{
		print_env_error(arg[1]);
		return 127;
	}
	while (tmp)
	{
		if (tmp->dx == 0 || tmp->dx == 2)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return 0;
}

