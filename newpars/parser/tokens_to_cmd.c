#include "minishell.h"

t_command *fill_cmd_assit1(t_command **cmd_list)
{
    t_command *new = create_command();
    if (!*cmd_list) {
        *cmd_list = new;
    } else {
        t_command *tmp = *cmd_list;
        while (tmp->next) 
            tmp = tmp->next;
        tmp->next = new;
    }
    return new;
}

void fill_cmd_assit(t_token *token, t_command *cmd, int *arg_count)
{
    if (token->type == WORD || token->type == S_QUOTE || token->type == D_QUOTE || token->type == ENV)
        add_arg(&cmd->args, arg_count, token->value);  
    else if (token->type >= RED_IN && token->type <= HERE_DOC)
    {
        if (token->next)
        {
            if (token->type == RED_IN || token->type == HERE_DOC)
                add_red(&cmd->in, token->next->value, token->type);  
            else
                add_red(&cmd->out, token->next->value, token->type); 
        }
    }
}

t_command *fill_command(t_token *tokens)
{
    t_command *cmd_list = NULL;
    t_command *cur = NULL;
    int arg_count = 0;

    while (tokens)
    {
        if (!cur || tokens->type == PIPE)
        {
            cur = fill_cmd_assit1(&cmd_list);
            arg_count = 0; 
        }
        fill_cmd_assit(tokens, cur, &arg_count);
        if (tokens->type >= RED_IN && tokens->type <= HERE_DOC)
            tokens = tokens->next;
        tokens = tokens->next;
    }
    return cmd_list;
}