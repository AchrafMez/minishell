#include "minishell.h"

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