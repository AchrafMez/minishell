#include "minishell.h"


void free_path(char **path)
{
    int i = 0;
    while(path[i])
    {
        free(path[i]);
        i++;
    }
    free(path);
}

char *get_path(char *target)
{
    char *env_path = getenv("PATH");
    if(!env_path)
        return NULL;
    char **path = ft_split(env_path,':');
    if(!path)
        return NULL;
    int i = 0;
    while(path[i])
    {
        char *slash_dir = ft_strjoin(path[i], "/");
        if(!slash_dir)
        {
            free_path(path);
            return NULL;
        }
        char *full_path = ft_strjoin(slash_dir, target);
        free(slash_dir);
        if(!full_path)
        {
            free_path(path);
            return NULL;
        }
        if(access(full_path, X_OK) == 0)
        {
            free_path(path);
            return full_path;
        }
        free(full_path);
        i++;   
    }
    free_path(path);
    return NULL;
}

void set_path(t_command **cmd)
{
    t_command *cur = *cmd;

    while (cur)
    {
        if (cur->args && cur->args[0]) // Check if args and args[0] exist
        {
            char *path = get_path(cur->args[0]);
            if (path != NULL)
            {
                cur->path = path;
                free(cur->args[0]);
                cur->args[0] = ft_strdup(cur->path);
            }
            else
            {
                cur->path = ft_strdup(cur->args[0]);
            }
        }
        cur = cur->next;
    }
}
