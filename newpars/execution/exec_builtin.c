/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:23:08 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/25 02:21:40 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_built_in(t_command *command)
{
    char *built_in[7];

    built_in[0] = "echo";
    built_in[1] = "cd";
    built_in[2] = "pwd";
    built_in[4] = "export";
    built_in[5] = "unset";
    built_in[3] = "env";
    built_in[6] = "exit";

    int i = 0;
    
    while(i < 7)
    {
        if(ft_strcmp(command->name, built_in[i]) == 0)
        {
            // printf("built in\n");
            return 1;
        }
        i++;
    }
    printf("not built in\n");
    return 0;
}

void exec_built(t_command *cmd, t_env **env)
{
    if(ft_strcmp(cmd->name, "pwd") == 0)
        pwd();
    else if(ft_strcmp(cmd->name, "cd") == 0)
        cd(cmd->args, *env);
    else if(ft_strcmp(cmd->name, "env") == 0)
        ft_enva(env,cmd->args);
    else if(ft_strcmp(cmd->name, "export") == 0)
        export(cmd->args, env);
    else if(ft_strcmp(cmd->name, "echo") == 0)
        echo(cmd->args);
    else if(ft_strcmp(cmd->name, "unset") == 0)
        unset(cmd->args, env);
    else if(ft_strcmp(cmd->name, "exit") == 0)
        ft_exit(cmd->args, 0);
}
