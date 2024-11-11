#include "../minishell.h"

int handle_double_quote(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env *env)
{
    (*cur)++; 
    while (**cur && **cur != '"')
    {
        if (**cur == '$')
            handle_dollar(cur, buffer, buf_idx, token_list, &env, 0); 
        else
            buffer[(*buf_idx)++] = *(*cur)++;
    }
    if (**cur == '\0')
    {
        printf("Error -> unclosed double quotes\n");
        return 1;
    }
    (*cur)++; 
    while (**cur && **cur != ' ' && **cur != '|')
    {
        if (**cur == '$')
            handle_dollar(cur, buffer, buf_idx, token_list, &env, 0);
        else if (**cur == '\'')
        {
            (*cur)++;
            while (**cur && **cur != '\'')
                buffer[(*buf_idx)++] = *(*cur)++;
            if (**cur == '\'')
                (*cur)++;
        }
        else if (**cur == '\"')
            handle_double_quote(cur, buffer, buf_idx, token_list, env);
        else
            buffer[(*buf_idx)++] = *(*cur)++;
    }

    buffer[*buf_idx] = '\0';

    add_token(token_list, create_token(buffer, D_QUOTE));
    *buf_idx = 0;
    return 0;
}


int handle_single_quote(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env *env)
{
    (*cur)++;
    while (**cur && **cur != '\'')
        buffer[(*buf_idx)++] = *(*cur)++;
    if (**cur == '\0') {
        printf("Error -> unclosed single quote\n");
        return 1;
    }
    (*cur)++;

    while (**cur && **cur != ' ' && **cur != '|')
    {
        if (**cur == '$')
            handle_dollar(cur, buffer, buf_idx, token_list, &env, 0);
        else if (**cur == '\'') {
            if (handle_single_quote(cur, buffer, buf_idx, token_list, env))
                return 1;  
        }
        else if (**cur == '\"') {
            (*cur)++; 

            while (**cur && **cur != '\"')
            {
                if (**cur == '$')
                    handle_dollar(cur, buffer, buf_idx, token_list, &env, 0);
                else
                    buffer[(*buf_idx)++] = *(*cur)++;
            }

            if (**cur == '\0')
            {
                printf("Error -> unclosed double quote\n");
                return 1;
            }
            (*cur)++;
        }
        else
            buffer[(*buf_idx)++] = *(*cur)++;
    }

    buffer[*buf_idx] = '\0';
    add_token(token_list, create_token(buffer, S_QUOTE));
    *buf_idx = 0;

    return 0;
}

