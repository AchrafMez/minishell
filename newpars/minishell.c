#include "minishell.h"

int check_syntax(t_token *token)
{
    t_token *cur = token;

    while(cur)
    {
        if(cur->type == PIPE)
        {
            if(!cur->next || cur->next->type == PIPE)
            {
                printf("minishell$: syntax error near '|' \n");
                return 1;
            }
        }
        else if(cur->type == RED_IN || cur->type == RED_OUT || cur->type == HERE_DOC ||cur->type == RED_APP)
        {
            if(!cur->next || (cur->next->type != WORD && cur->next->type != SPACES && cur->next->type != S_QUOTE && cur->next->type != D_QUOTE))
            {
                printf("minishell$: syntax error near > < \n");
                return 1;
            }
        }
        cur = cur->next;
    }
    return 0;
}

int check_unclosed_quotes(char *input)
{
    int s_quotes = 0;
    int d_quotes = 0;
    while (*input)
    {
        if (*input == '\'' && !d_quotes)
            s_quotes = !s_quotes;
        else if (*input == '"' && !s_quotes)
                d_quotes = !d_quotes;
        input++;
    }
    if (s_quotes)
    {
        printf("minishell$: singel quotes not closed\n");
        return 1;
    }
    if(d_quotes)
    {
        printf("minishell$: double quotes not closed\n");
        return 1;
    }
    return 0;  
}

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