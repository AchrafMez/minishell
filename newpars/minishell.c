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
                printf("syntax error || \n");
                return 1;
            }
        }
        else if(cur->type == RED_IN || cur->type == RED_OUT || cur->type == HERE_DOC ||cur->type == RED_APP)
        {
            if(!cur->next || (cur->next->type != WORD && cur->next->type != SPACES && cur->next->type != S_QUOTE && cur->next->type != D_QUOTE))
            {
                printf("syntax error > < \n");
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
        printf("singel quotes not closed\n");
        return 1;
    }
    if(d_quotes)
    {
        printf("double quotes not closed\n");
        return 1;
    }
    return 0;  
}




void leaks()
{
    system("leaks minishell");
}

void print_cmd(t_command *command)
{
    t_command *cur = command;
    while(cur)
    {
        int i = 0;
        printf("cmd path: %s\n", cur->path);
        while(cur->args[i])
        {
            printf("arg: %s\n", cur->args[i]);
            i++;
        }
        t_red *tmp = cur->in;
        t_red *out_tm = cur->out;
        while(out_tm)
        {
            printf("ouput file: %s typt: %u\n", out_tm->value, out_tm->type);
            out_tm = out_tm->next;
        }
        while(tmp)
        {
            printf("input file: %s typt: %u\n", tmp->value, tmp->type);
            tmp = tmp->next;
        }
        printf("------- another cmd -------\n");
        cur = cur->next;
    }
}

void free_cmd(t_command *command)
{
    t_command *cur = command;
    t_command *next ;
    while(cur)
    {
        next = cur->next;
        int i = 0;
        while(cur->args[i])
        {
            free(cur->args[i]);
            i++;
        }
        free(cur->args);
        free(cur->path);
        t_red *red_tmp = cur->in;
        while(red_tmp)
        {
            t_red *next_red = red_tmp->next;
            free(red_tmp->value);
            free(red_tmp);
            red_tmp = next_red;
        }
        t_red *red_out = cur->out;
        while(red_out)
        {
            t_red *next_out = red_out->next;
            free(red_out->value);
            free(red_out);
            red_out = next_out;
        }
        free(cur);
        cur = next;
    }
}

void free_path(char **path)
{
    int i = 0;
    while(path[i])
    {
        free(path[i]);
        i++;
    }
    free(path);
}
char *get_path(char *target)
{
    char *env_path = getenv("PATH");
    if(!env_path)
        return NULL;
    char **path = ft_split(env_path,':');
    if(!path)
        return NULL;
    int i = 0;
    while(path[i])
    {
        char *slash_dir = ft_strjoin(path[i], "/");
        if(!slash_dir)
        {
            free_path(path);
            return NULL;
        }
        char *full_path = ft_strjoin(slash_dir, target);
        free(slash_dir);
        if(!full_path)
        {
            free_path(path);
            return NULL;
        }
        if(access(full_path, X_OK) == 0)
        {
            free_path(path);
            return full_path;
        }
        free(full_path);
        i++;   
    }
    free_path(path);
    return NULL;
}
void set_path(t_command **cmd)
{
    t_command *cur = *cmd;

    while (cur)
    {
        if (cur->args && cur->args[0]) // Check if args and args[0] exist
        {
            char *path = get_path(cur->args[0]);
            if (path != NULL)
            {
                cur->path = path;
                free(cur->args[0]);
                cur->args[0] = ft_strdup(cur->path);
            }
            else
            {
                cur->path = ft_strdup(cur->args[0]);
            }
        }
        cur = cur->next;
    }
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