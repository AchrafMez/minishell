#include "../minishell.h"


void cd(char **args, t_env *env)
{
    char *target;
    char *cwd = NULL;
    char *new;

    if(!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        target = get_env_value(env, "HOME");
        printf("%s", target);
        if(!target)
        {
            printf("cd");
            return ;
        }
    }
    else if(ft_strcmp(args[1], "-") == 0)
    {
        target = get_env_value(env, "OLDPWD");
        printf("%s\n", target);
    }
    else
    {
        target = args[1];
        // printf("%s\n", target);
    }
    cwd = getcwd(NULL, 0);
    if(!cwd)
    {
        printf("cwd fail");
        return ;
    }
    set_env_value(&env, "OLDPWD", cwd);
    free(cwd);
    if(chdir(target) != 0)
    {
        perror("cd");
        return;
    }
    new = getcwd(NULL, 0);
    if(new)
    {
        set_env_value(&env, "PWD", new);
        free(new);;
    }
    else
        perror("minishell: cd");

}
