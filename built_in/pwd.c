/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:11 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/05 07:48:39 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		// set_export_env(env, "?", "0");
		update_exit_value(env, 0);
		return (0);
	}
	else
	{
		printf("errror\n");
		// set_export_env(env, "?", "1");
		update_exit_value(env, 1);
		return (1);
	}
}
