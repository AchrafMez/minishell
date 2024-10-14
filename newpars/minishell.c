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
            if(!cur->next || cur->next->type != WORD)
            {
                printf("syntax errer > < \n");
                return 1;
            }
        }
        cur = cur->next;
    }
    return 0;
}

void handl_input()
{
    char *input;
    t_token *token_list;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break ;
        add_history(input);
        token_list = tokenize_input(input);
        if(check_syntax(token_list) == 0)
            print_tokens(token_list);
        ft_tokens_free(token_list);
        free(input);
    }
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)ac;
    // (void)envp;
    t_env *env = NULL;
    dup_env(envp, &env);
    char *searsh = get_env_value(env,"USER");
    printf("searsh: %s\n", searsh);

    // if(ac == 1)
    //     handl_input();
    return 0;
}