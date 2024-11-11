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
            //cur.next != word || next != space
            if(!cur->next || (cur->next->type != WORD && cur->next->type != SPACES && cur->next->type != S_QUOTE && cur->next->type != D_QUOTE))
            {
                printf("syntax errer > < \n");
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

// int count_list(t_token *token_lis)
// {
//     t_token *cur = token_lis;
//     printf("Count list func \n");
//     int count = 0;
//     while(cur)
//     {
//         if(cur->type == PIPE || cur->type == RED_IN || cur->type == RED_OUT || cur->type == RED_APP || cur->type == HERE_DOC)
//             break ;
//         count++;
//         cur = cur->next;
//     }
//     return count;
// }

// t_command *fill_command(t_token *token_list) {
//     t_command *command_list = NULL;
//     t_command *current_cmd = NULL;
//     t_token *tokens = token_list;
//     int arg_count = 0;

//     while (tokens)
//     {
//         // printf("test\n");
//         if (!current_cmd)
//         {
//             current_cmd = create_command();

//             if (!command_list)
//                 command_list = current_cmd;
//             else
//             {
//                 t_command *temp = command_list;
//                 while (temp->next)
//                     temp = temp->next;
//                 temp->next = current_cmd;
//             }
//         }

//         if (tokens->type == WORD || tokens->type == S_QUOTE || tokens->type == D_QUOTE || tokens->type == ENV)
//         {
//             // printf("here\n");
//             add_arg(&current_cmd->args, &arg_count, tokens->value);
//         }
//         else if (tokens->type >= RED_IN && tokens->type <= HERE_DOC)
//         {
//             // printf("here1\n");
//             if (tokens->next)
//             {
//                 // printf("here2\n");
//                 add_red(&current_cmd->red, tokens->next->value, tokens->type);
//             }
//             tokens = tokens->next;
//         }
        
//         else if (tokens->type == PIPE)
//             current_cmd = NULL; 

//         tokens = tokens->next;
//     }
//     return command_list;
// }
// t_command *fill_command(t_token *token_list)
// {
//     t_command *command_list = NULL;
//     t_command *current_cmd = NULL;
//     t_token *tokens = token_list;
//     int arg_count = 0;

//     while(tokens)
//     {
//         if(!current_cmd) {
//             current_cmd = create_command();

//             if(!command_list)
//                 command_list = current_cmd;
//             else
//             {
//                 t_command *temp = command_list;
//                 while (temp->next)
//                     temp = temp->next;
//                 temp->next = current_cmd;
//             }
//         }
//         if (tokens->type == WORD || tokens->type == S_QUOTE || tokens->type == D_QUOTE || tokens->type == ENV)
//             add_arg(&current_cmd->args, &arg_count, tokens->value);
//         else if (tokens->type == RED_IN || tokens->type == HERE_DOC)
//         {
//             if (tokens->next)
//             {
//                 add_red(&current_cmd->in, tokens->next->value, tokens->type);
//                 tokens = tokens->next;
//             }
//         }
//         else if (tokens->type == RED_OUT || tokens->type == RED_APP)
//         {
//             if (tokens->next) {
//                 add_red(&current_cmd->out, tokens->next->value, tokens->type);
//                 tokens = tokens->next;
//             }
//         }
//         else if (tokens->type == PIPE)
//         {
//             current_cmd = NULL;
//             arg_count = 0;
//         }
//         tokens = tokens->next;
//     }
//     return command_list;
// }



void delete_space(t_token **token_list)
{
    t_token *cur = *token_list;
    t_token *prev = NULL;
    if(cur && (cur->type == SPACES || ft_strcmp(cur->value, "") == 0))
    {
        // printf("1\n");
        *token_list = cur->next;
        free(cur->value);
        free(cur);
        return ;
    }
    while(cur != NULL && (cur->type != SPACES && ft_strcmp(cur->value, "")))
    {
        // printf("2\n");
        prev = cur;
        cur = cur->next;
    }
    if(cur != NULL)
    {
        // printf("3\n");
        prev->next = cur->next;
        free(cur->value);
        free(cur);
    }
}

void tokens_edit(t_token **token_list)
{
    t_token *cur = *token_list;
    // printf("0\n");
    while(cur)
    {
        if(cur->type == SPACES || cur->value[0] == '\0')
            delete_space(token_list);
        cur = cur->next;
    }
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
            // printf("file type: |%u|\n", cur->red->type);
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
    // int found = 0;
    while (cur)
    {
        printf("seet path\n");
        char *path = get_path(cur->args[0]);
        if(path!= NULL)
        {
            // found = 1;
            cur->path = path;
            free(cur->args[0]);
            cur->args[0] = ft_strdup(cur->path);
            if(!cur->args[0])
            {
                printf("strdup errror\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            cur->path = ft_strdup(cur->args[0]);
            if(!cur->path)
            {
                printf("srdup 2 error\n");
                exit(EXIT_FAILURE);
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
            break ;
        if(check_unclosed_quotes(input))
        {
            free(input);
            continue ;
        }
        add_history(input);
        token_list = tokenize_input(input, env);
        // ft_free_env(env);
        if(check_syntax(token_list) == 0)
        {
            // print_tokens(token_list);
            // printf("------------ after deleted ------------\n");
            tokens_edit(&token_list);
            // print_tokens(token_list);
            // int count = count_list(&token_list);
            // printf("count list: %d\n", count);
            cmd = fill_command(token_list);
            set_path(&cmd);
            print_cmd(cmd);
            // free_cmd(cmd);
            // execute_cmds(cmd);
        // ft_tokens_free(token_list);
        }
        free_cmd(cmd);
        ft_tokens_free(token_list);
        free(input);
        system("leaks minishell");
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

