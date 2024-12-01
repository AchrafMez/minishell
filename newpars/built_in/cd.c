/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:13 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/01 04:29:06 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cd(char **args, t_env *env)
{
    char *target;
    char *cwd = NULL;
    char *new;

    if (!args[1])
    {
        target = get_env_value(env, "HOME");
        if (!target)
        {
            printf("cd: HOME not set\n");
            return 1;
        }
    }
    else
        target = args[1];
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("cd: getcwd");
        return 1;
    }

    set_env_value(&env, "OLDPWD", cwd);
    free(cwd);

    if (chdir(target) != 0)
    {
        perror("cd");
        return 1;
    }

    new = getcwd(NULL, 0);
    if (new)
    {
        set_env_value(&env, "PWD", new);
        free(new);
    }
    else
    {
        perror("cd: getcwd");
        return 1;
    }
    return 0;
}

