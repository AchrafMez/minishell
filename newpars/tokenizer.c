#include "minishell.h"

void handle_space(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    if (*buf_idx > 0)
    {
        buffer[*buf_idx] = '\0';
        add_token(token_list, create_token(buffer, WORD));
        *buf_idx = 0;
    }
    add_token(token_list, create_token(" ", SPACES));
    (*cur)++;
}

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



int handle_pipe(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    if(!*token_list)
    {
        printf("syntax error near unexpected token '|'\n");
        return 1;
    }
    if (*buf_idx > 0)
    {
        buffer[*buf_idx] = '\0';
        add_token(token_list, create_token(buffer, WORD));
        *buf_idx = 0;
    }
    add_token(token_list, create_token("|", PIPE));
    (*cur)++;
    return 0;
}

int handle_red_in(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    if (*buf_idx > 0)
    {
        buffer[*buf_idx] = '\0';
        add_token(token_list, create_token(buffer, WORD));
        *buf_idx = 0;
    }
    if(*(*cur + 1) == '<')
    {
        add_token(token_list, create_token("<<", HERE_DOC));
        (*cur)++;
    }
    else
        add_token(token_list, create_token("<", RED_IN));
    (*cur)++;
    if(**cur == '<' || **cur == '>')
    {
        printf("syntax error near unexpected token '<' \n");
        return 1;
    }
    return 0;
}

int handle_red_out(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    if (*buf_idx > 0)
    {
        buffer[*buf_idx] = '\0';
        add_token(token_list, create_token(buffer, WORD));
        *buf_idx = 0;
    }
    if (*(*cur + 1) == '>')
    {
        add_token(token_list, create_token(">>", RED_APP));
        (*cur)++;
    } 
    else
        add_token(token_list, create_token(">", RED_OUT));
    (*cur)++;
    if(**cur == '>' || **cur == '<')
    {
        printf("Syntax error near unexpected token '>' \n");
        return 1;
    }
    return 0;
}

void handle_dollar(char **cur, char *buffer, int *buf_idx, t_token **token_list, t_env **env, int flag)
{
    (*cur)++;
    char key[64];
    int key_idx = 0;
    while(**cur &&(ft_isalnum(**cur) || **cur == '_'))
        key[key_idx++] = *(*cur)++;
    key[key_idx] = '\0';
    printf("key: %s\n", key);
    char *expanded = get_env_value(*env, key);
    int i = 0;
    if(expanded)
    {
        while(expanded[i] != '\0')
            buffer[(*buf_idx)++] = expanded[i++];
        printf("expanded: %s\n", expanded);
        if(flag == 1)
        {
            add_token(token_list, create_token(expanded, ENV));
            *buf_idx = 0;
        }
    }
    else
    {
        i = 0;
        buffer[(*buf_idx)] = '$';
        while(key[i] != '\0')
            buffer[(*buf_idx)++] = key[i++];
        printf("key2%s\n", key);
         if(flag == 1)
        {
            add_token(token_list, create_token(buffer, WORD));
            *buf_idx = 0;
        }
    }
}

t_token *tokenize_input(char *input, t_env **env)
{
    t_token *token_list = NULL;
    char *cur = input;
    char buffer[1024];
    int buf_idx = 0;

    while (*cur)
    {
        if (*cur == ' ')
            handle_space(&cur, buffer, &buf_idx, &token_list);
        else if (*cur == '"')
        {
            int dq = handle_double_quote(&cur, buffer, &buf_idx, &token_list, *env);
            if(dq == 1)
            {
                ft_tokens_free(token_list);
                return NULL;
            }
        }
        else if (*cur == '\'')
        {
            int ret = handle_single_quote(&cur, buffer, &buf_idx, &token_list, *env);
            if(ret == 1)
            {
                ft_tokens_free(token_list);
                return NULL;
            }        
        }
        else if (*cur == '|')
            {
                int pipe = handle_pipe(&cur, buffer, &buf_idx, &token_list);
                if(pipe == 1)
                {
                    ft_tokens_free(token_list);
                    return NULL;
                }
            }
        else if (*cur == '<')
        {
            int red_out = handle_red_in(&cur, buffer, &buf_idx, &token_list);
            if(red_out == 1)
            {
                ft_tokens_free(token_list);
                return NULL;
            }
        }
        else if (*cur == '>')
        {
            int red = handle_red_out(&cur, buffer, &buf_idx, &token_list);
            if(red == 1)
            {
                ft_tokens_free(token_list);
                return NULL;
            }
        }
        else if (*cur == '$')
            handle_dollar(&cur, buffer, &buf_idx, &token_list, env, 1);
        else
        {
            buffer[buf_idx++] = *cur;
            cur++;
        }
    }
    if (buf_idx > 0)
    {
        buffer[buf_idx] = '\0';
        add_token(&token_list, create_token(buffer, WORD));
    }
    return token_list;
}
