#include "../minishell.h"

int echo(char **args)
{
    int counter;
    int n_flag = 0;

    counter = 1;
    if(ft_strcmp(args[counter], "-n") == 0)
    {
        counter++;
        n_flag = 1;
    }
    while(args[counter])
    {
        printf("%s", args[counter]);
        if(args[counter + 1] != NULL)
            printf(" ");
        counter++;
    }
    if(n_flag != 1)
        printf("\n");
    return 0;
}

int main()
{
    char *args[] = {"echo" ,"-n", "world","world","world","world","world","world","world","world","world","world","world","test", NULL};
    echo(args);
}