/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:13:12 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/18 11:43:21 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void leaks()
{
    system("leaks minishell");
}

void handl_input(t_env **env, t_shell *shell)
{
    char *input;
    t_token *token_list = NULL;
    t_command *cmd = NULL;
    (void)shell;
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
            cmd = fill_command(token_list, *env);
            if(cmd)
            {
                set_path(&cmd);
                // print_tokens(token_list);
                // shell->exit_status = execute_command(cmd, shell);
                // print_cmd(cmd);
                // if(is_built_in(cmd) == 1)
                    // exec_built(cmd, env);
                execution(&cmd, env);
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
    handle_signals();
    // (void)envp;
    t_env *env = NULL;
    dup_env(envp, &env);
    set_export_env(&env, "?", "0");
    t_shell shell;
    shell.env = env;
    shell.exit_status = 0;
    if(ac == 1)
        handl_input(&env, &shell);
    return 0;
}
