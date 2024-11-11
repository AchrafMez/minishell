#include "../minishell.h"

void delete_space(t_token **token_list)
{
    t_token *cur = *token_list;
    t_token *prev = NULL;
    if(cur && (cur->type == SPACES || ft_strcmp(cur->value, "") == 0))
    {
        *token_list = cur->next;
        free(cur->value);
        free(cur);
        return ;
    }
    while(cur != NULL && (cur->type != SPACES && ft_strcmp(cur->value, "")))
    {
        prev = cur;
        cur = cur->next;
    }
    if(cur != NULL)
    {
        prev->next = cur->next;
        free(cur->value);
        free(cur);
    }
}

void tokens_edit(t_token **token_list)
{
    t_token *cur = *token_list;
    while(cur)
    {
        if(cur->type == SPACES || cur->value[0] == '\0')
            delete_space(token_list);
        cur = cur->next;
    }
}