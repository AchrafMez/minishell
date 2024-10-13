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

void handle_double_quote(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    (*cur)++;
    while (**cur && **cur != '"')
        buffer[(*buf_idx)++] = *(*cur)++;
    buffer[*buf_idx] = '\0';
    add_token(token_list, create_token(buffer, D_QUOTE));
    *buf_idx = 0;
    if (**cur)
        (*cur)++;
}

void handle_single_quote(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    (*cur)++;
    while (**cur && **cur != '\'')
        buffer[(*buf_idx)++] = *(*cur)++;
    buffer[*buf_idx] = '\0';
    add_token(token_list, create_token(buffer, S_QUOTE));
    *buf_idx = 0;
    if (**cur)
        (*cur)++;
}

void handle_pipe(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    if (*buf_idx > 0)
    {
        buffer[*buf_idx] = '\0';
        add_token(token_list, create_token(buffer, WORD));
        *buf_idx = 0;
    }
    add_token(token_list, create_token("|", PIPE));
    (*cur)++;
}

void handle_red_in(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    if (*buf_idx > 0)
    {
        buffer[*buf_idx] = '\0';
        add_token(token_list, create_token(buffer, WORD));
        *buf_idx = 0;
    }
    add_token(token_list, create_token("<", RED_IN));
    (*cur)++;
}

void handle_red_out(char **cur, char *buffer, int *buf_idx, t_token **token_list)
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
}

void handle_dollar(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
    buffer[(*buf_idx)++] = *(*cur)++;
    while (**cur && (ft_isalnum(**cur) || **cur == '_'))
        buffer[(*buf_idx)++] = *(*cur)++;
    buffer[*buf_idx] = '\0';
    add_token(token_list, create_token(buffer, ENV));
    *buf_idx = 0;
}

t_token *tokenize_input(char *input)
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
            handle_double_quote(&cur, buffer, &buf_idx, &token_list);
        else if (*cur == '\'')
            handle_single_quote(&cur, buffer, &buf_idx, &token_list);
        else if (*cur == '|')
            handle_pipe(&cur, buffer, &buf_idx, &token_list);
        else if (*cur == '<')
            handle_red_in(&cur, buffer, &buf_idx, &token_list);
        else if (*cur == '>')
            handle_red_out(&cur, buffer, &buf_idx, &token_list);
        else if (*cur == '$')
            handle_dollar(&cur, buffer, &buf_idx, &token_list);
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
