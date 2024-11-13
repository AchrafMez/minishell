/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:13:12 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/13 13:00:53 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void leaks()
{
    system("leaks minishell");
}

void handl_input(t_env **env)
{
    char *input;
    t_token *token_list = NULL;
    t_command *cmd = NULL;
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            ctrl_d();
        if(check_unclosed_quotes(input))
        {
            add_history(input);
            free(input);
            continue ;
        }
        add_history(input);
        token_list = tokenize_input(input, env);
        if(token_list)
            tokens_edit(&token_list);
        if(token_list && check_syntax(token_list) == 0)
        {
            cmd = fill_command(token_list);
            if(cmd)
            {
                set_path(&cmd);
                print_cmd(cmd);
                // execution(&cmd, env);
                free_cmd(cmd);
            }
        }
        free(input);
        ft_tokens_free(token_list);
        // system("leaks minishell");
        // atexit(leaks);
    }
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)ac;
    // (void)envp;
    t_env *env = NULL;
    dup_env(envp, &env);
    // display_env(env);
    // char **path = ft_split(getenv("PATH"),':');
    // for(int i = 0; path[i] != NULL; i++)
    //     printf("path[i]: %s\n", path[i]);
    
    handle_signals();
    if(ac == 1)
        handl_input(&env);
    return 0;

}