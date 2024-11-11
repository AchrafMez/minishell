#include "builtin.h"
int	ft_strcmp(const char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s1[i])
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
static int	nbrarray(char const *s, char c)
{
	int i;
	int j;
	int nbrstr;

	i = 0;
	nbrstr = 0;
	while (s[i])
	{
		j = i;
		while (s[j] != c && s[j])
			j++;
		if (j > i)
		{
			i = j;
			nbrstr++;
			continue ;
		}
		i++;
	}
	return (nbrstr);
}

void	frealltab(char **str)
{
	int l;

	l = 0;
	while (str[l])
	{
		free(str[l++]);
	}
	return ;
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int i;
	unsigned int l;
	char *str;

	i = 0;
	l = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	else
		str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] && i < start)
		i++;
	while (len-- > 0 && s[i])
		str[l++] = s[i++];
	str[l] = '\0';
	return (&str[0]);
}
static int	checkimpli(char const *s, char **str, char c)
{
	int i;
	int j;
	int l;

	i = -1;
	l = 0;
	while (s[++i])
	{
		j = i;
		while (s[j] != c && s[j])
			j++;
		if (j > i)
		{
			str[l] = ft_substr(&s[i], 0, j - i);
			if (!str[l++])
			{
				frealltab(str);
				return (1);
			}
			i = j - 1;
		}
	}
	str[l] = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char **str;
	int i;

	if (!s)
		return (NULL);
	str = malloc((nbrarray(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = checkimpli(s, str, c);
	if (i == 1)
	{
		free(str);
		return (NULL);
	}
	return (str);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char *p;
	int j;
	int i;

	if (!s1 || !s2)
		return (0);
	j = 0;
	i = 0;
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (0);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}
int	ft_size_list(t_cmd *list)
{
	int cnt;
	t_cmd *tmp;

	tmp = list;
	cnt = 0;
	while (tmp)
	{
		cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
void	ft_lstadd_front_env(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}
t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	if (!*lst)
	{
		ft_lstadd_front_env(lst, new);
		return ;
	}
	ft_lstlast_env(*lst)->next = new;
}
t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env *lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = key;
	lst->value = value;
	lst->next = NULL;
	return (lst);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *ptr_d;
	char *ptr_s;

	i = 0;
	ptr_d = (char *)dest;
	ptr_s = (char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*ptr_d++ = *ptr_s++;
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char *str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, ft_strlen(s) + 1);
	return (str);
}

char	**ft_strplit(char *env)
{
	int i;
	char **str;
	int len;

	str = NULL;
	i = -1;
	len = ft_strlen(env);
	while (env[++i] && env[i] != '=')
		;
	str = malloc(sizeof(char *) * 3);
	str[0] = ft_substr(&env[0], 0, i);
	if (!env[i])
		str[1] = ft_strdup("");
	else
		str[1] = ft_substr(&env[i], 1, len);
	str[2] = 0;
	return (str);
}