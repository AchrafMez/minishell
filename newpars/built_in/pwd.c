#include "../minishell.h"

int pwd(void)
{
    char *cwd;
    // printf("zaaaba\n");
    cwd = getcwd(NULL, 0);
    if(cwd)
    {
        printf("%s\n", cwd);
        free(cwd);
        return 0;
    }
    else
    {
        printf("errror\n");
        return 1;
    }
}
