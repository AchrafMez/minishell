#include "minishell.h"

int ft_strcmp(char *str, char *target)
{
    int i = 0;
    if(!str && !target)
        return 1;
    while(str[i] && target[i])
    {
        if(str[i] != target[i])
            return 1;
        i++;
    }
    return 0;
}