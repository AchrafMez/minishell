#include "minishell.h"



// void handl_input()
// {
//     char *input;
//     while(1)
//     {
//         input =  readline("minishell$");
//         if(!input)
//             break ;
//         add_history(input);
//         printf("%s\n", input);
//         free(input);
//     }
// }

t_token *tokenize_input(char *input)
{
    t_token *token_list = NULL;
    char *cur = input;
    char buffer[1024];
    int buf_index = 0;

    while (*cur)
    {
        if (*cur == ' ')
        {
            if (buf_index > 0)
            {
                buffer[buf_index] = '\0';
                add_token(&token_list, create_token(buffer, WORD));
                buf_index = 0;
            }
            add_token(&token_list, create_token(" ", SPACES));
        }
        else if (*cur == '"')
        {
            cur++;
            while (*cur && *cur != '"')
            {
                buffer[buf_index++] = *cur++;
            }
            buffer[buf_index] = '\0';
            add_token(&token_list, create_token(buffer, D_QUOTE));
            buf_index = 0;
        }
        else if (*cur == '\'')
        {
            cur++;
            while (*cur && *cur != '\'')
            {
                buffer[buf_index++] = *cur++;
            }
            buffer[buf_index] = '\0';
            add_token(&token_list, create_token(buffer, S_QUOTE));
            buf_index = 0;
        }
        else if (*cur == '|')
        {
            if (buf_index > 0)
            {
                buffer[buf_index] = '\0';
                add_token(&token_list, create_token(buffer, WORD));
                buf_index = 0;
            }
            add_token(&token_list, create_token("|", PIPE));
        }
        else if (*cur == '<')
        {
            if (buf_index > 0)
            {
                buffer[buf_index] = '\0';
                add_token(&token_list, create_token(buffer, WORD));
                buf_index = 0;
            }
            if (*(cur + 1) == '<')
            {
                add_token(&token_list, create_token("<<", HERE_DOC));
                cur++;
            }
            else
            {
                add_token(&token_list, create_token("<", RED_IN));
            }
        }
        else if (*cur == '>')
        {
            if (buf_index > 0)
            {
                buffer[buf_index] = '\0';
                add_token(&token_list, create_token(buffer, WORD));
                buf_index = 0;
            }
            if (*(cur + 1) == '>')
            {
                add_token(&token_list, create_token(">>", RED_APP));
                cur++;
            }
            else
            {
                add_token(&token_list, create_token(">", RED_OUT));
            }
        }
        else if (*cur == '$')
        {
            buffer[buf_index++] = *cur;
            cur++;
            while (*cur && (ft_isalnum(*cur) || *cur == '_'))
            {
                buffer[buf_index++] = *cur++;
            }
            buffer[buf_index] = '\0';
            add_token(&token_list, create_token(buffer, ENV));
            buf_index = 0;
            continue;
        }
        else
        {
            buffer[buf_index++] = *cur;
        }
        cur++;
    }
    if (buf_index > 0)
    {
        buffer[buf_index] = '\0';
        add_token(&token_list, create_token(buffer, WORD));
    }
    return token_list;
}
void handl_input()
{
    char *input;
    t_token *token_list;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;
        add_history(input);
        token_list = tokenize_input(input);
        print_tokens(token_list);
        ft_tokens_free(token_list);
        free(input);
    }
}

int main(int ac, char **av, char **env)
{
    (void)av;
    (void)env;
    if(ac == 1)
        handl_input();
    return 0;
}