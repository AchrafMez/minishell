#include "minishell.h"

static int	count(char const *s, char c)
{
    int	i;
    int	wcount;

    i = 0;
    wcount = 0;
    while (s && s[i])
    {
        while (s[i] && s[i] == c)
            i++;
        if (s[i] != '\0' && s[i] != c)
            wcount++;
        while (s[i] && s[i] != c)
            i++;
    }
    return (wcount);
}

static int	word_len(char const *s, char c, int i)
{
    int	len;

    len = 0;
    while (s[i + len] && s[i + len] != c)
        len++;
    return (len);
}

static void	ft_free(char **new, int j)
{
    while (j >= 0)
    {
        free(new[j]);
        j--;
    }
    free(new);
}

int check_pipe(char *str, int i)
{
    char sing;
    int j = 0;
    while (str[j] && j < i)
    {
        if(str[j] == '\'' || str[j] == '\"')
            {
            sing = str[j];
            j++;
            while (str[j] && str[j] != sing && j< i)
            {
                j++;
            }
            if (str[j] != sing)
            {
                return 1;
            }
        }
        j++;
    }
    return 0;
}

char	**ft_taqsim(char *s, char c)
{
    int		i;
    int		j;
    char	**new;

    i = 0;
    j = 0;
    new = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
    if (!new)
        return (NULL);
    while (s && s[i] != '\0' && j < count(s, c))
    {
        while (s[i] && s[i] == c)
            i++;
        new[j] = ft_substr(s, i, word_len(s, c, i));
        if (!new[j])
        {
            ft_free(new, j);
            return (NULL);
        }
        i += word_len(s, c, i);
        j++;
    }
    new[j] = NULL;
    return (new);
}