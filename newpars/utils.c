#include "minishell.h"

int ft_strcmp(char *str, char *target)
{
    while(*str && (*str == *target))
    {
        str++;
        target++;
    }
    return *str - *target;
}
