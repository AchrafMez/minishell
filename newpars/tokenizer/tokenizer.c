#include "../minishell.h"

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

void handle_dollar(t_content *content, int flag)
{
    (*content->cur)++;
    char key[256];
    int key_idx = 0;
    while(**content->cur &&(ft_isalnum(**content->cur) || **content->cur == '_'))
        key[key_idx++] = *(*content->cur)++;
    key[key_idx] = '\0';
    // printf("key: %s\n", key);
    char *expanded = get_env_value(content->env, key);
    int i = 0;
    if(expanded)
    {
        while(expanded[i] != '\0')
            content->buffer[(*content->buf_idx)++] = expanded[i++];
        printf("expanded: %s\n", expanded);
        if(flag == 1)
        {
            add_token(content->token_list, create_token(expanded, ENV));
            *content->buf_idx = 0;
        }
    }
    else
    {
        i = 0;
        content->buffer[(*content->buf_idx)] = '$';
        while(key[i] != '\0')
            content->buffer[(*content->buf_idx)++] = key[i++];
        if(flag == 1)
        {
            add_token(content->token_list, create_token(content->buffer, WORD));
            *content->buf_idx = 0;
        }
    }
}

t_token *tokenize_input(char *input, t_env **env)
{
    t_token *token_list = NULL;
    char *cur = input;
    char buffer[1024];
    int buf_idx = 0;
    
    t_content content = {&cur, buffer, &buf_idx, &token_list, *env};
    while (*cur)
    {
        if (*cur == ' ')
            handle_space(&cur, buffer, &buf_idx, &token_list);
        else if (*cur == '"')
        {
            int dq = handle_double_quote(&content);
            if(dq == 1)
            {
                ft_tokens_free(token_list);
                return NULL;
            }
        }
        else if (*cur == '\'')
        {
            int ret = handle_single_quote(&content);
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
            handle_dollar(&content, 1);
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
