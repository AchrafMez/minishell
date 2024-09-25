#include "builtin.h"
// #include"./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t	ft_strlen(const char *str)
{
	size_t c;

	c = 0;
	while (*str != '\0')
	{
		str++;
		c++;
	}
	return (c);
}

char	*ft_strdup(const char *s)
{
	char *array;
	int size;
	int i;

	i = 0;
	size = 0;
	while (s[size] != '\0')
		size++;

	array = (char *)malloc(size + 1);
	if (array == NULL)
		return (NULL);

	while (i < size)
	{
		array[i] = s[i];
		i++;
	}
	array[i] = '\0';

	return (array);
}
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t s_len;
	char *new;
	size_t index;

	if ((start >= ft_strlen(s)))
		return (ft_strdup(""));
	s_len = ft_strlen(s);
	if (s_len < len + start)
		len = s_len - start;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	index = 0;
	while (index < len)
	{
		new[index] = s[start + index];
		index++;
	}
	new[index] = '\0';
	return (new);
}

char	*ft_strchr(const char *str, int character)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)character)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == (unsigned char)character)
		return ((char *)str + i);
	return (NULL);
}
char	*get_value(char *args)
{
	char	*equals;

	equals = strchr(args, '=');
	if (!equals)
		return (NULL);
	return (ft_strdup(equals + 1));
}
char	*get_name(char *args)
{
	char	*equals;
	size_t	len;
	char	*name;

	equals = strchr(args, '=');
	if (!equals)
		return (ft_strdup(args));
	len = equals - args;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strncpy(name, args, len);
	name[len] = '\0';
	return (name);
}

int	add_env_var(t_env **head, char *key, char *value)
{
	t_env *new;
	t_env *tmp;
	tmp = *head;

	while (tmp)
	{
		if (strcmp(tmp->name, key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = key;
	new->value = value;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}
int	ft_charfind(char *str, char c)
{
	int i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}
void	ft_create_env(t_env **head, char **env)
{
	char *name;
	char *value;
	int i = 0;
	while (env[i])
	{
		value = ft_strchr(env[i], '=') + 1;
		name = ft_substr(env[i], 0, ft_charfind(env[i], '='));
		add_env_var(head, name, value);
		i++;
	}
}
void	ft_print_env(t_env **head)
{
	t_env *tmp;
	tmp = *head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

t_env	ft_export(char **argv, char **env)
{
	t_env *env_list;
	env_list = NULL;
	ft_create_env(&env_list, env);

	int i = 1;

	if (argv[i] == NULL)
	{
		ft_print_env(&env_list);
		return (*env_list);
	}

	while (argv[i])
	{
		char *name = get_name(argv[i]);
		char *value = get_value(argv[i]);
		add_env_var(&env_list, name, value);
		i++;
	}
		ft_print_env(&env_list);

		return (*env_list);
	

}
int	main(int argc, char **argv, char **env)
{
	ft_export(argv, env);
	return (0);
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct s_env {
//     char *name;
//     char *value;
//     struct s_env *next;
// } t_env;

// size_t ft_strlen(const char *str) {
//     size_t c = 0;
//     while (str[c] != '\0') {
//         c++;
//     }
//     return c;
// }

// char *ft_strdup(const char *s) {
//     size_t size = ft_strlen(s);
//     char *array = (char *)malloc(size + 1);
//     if (array == NULL) {
//         return NULL;
//     }
//     strcpy(array, s);
//     return array;
// }

// char *ft_substr(const char *s, unsigned int start, size_t len) {
//     size_t s_len = ft_strlen(s);
//     if (start >= s_len) {
//         return ft_strdup("");
//     }
//     if (s_len < len + start) {
//         len = s_len - start;
//     }
//     char *new = (char *)malloc((len + 1) * sizeof(char));
//     if (new == NULL) {
//         return NULL;
//     }
//     strncpy(new, s + start, len);
//     new[len] = '\0';
//     return new;
// }

// char *get_value(const char *args) {
//     char *equals = strchr(args, '=');
//     if (!equals) {
//         return NULL;
//     }
//     return ft_strdup(equals + 1);
// }

// char *get_name(const char *args) {
//     char *equals = strchr(args, '=');
//     if (!equals) {
//         return ft_strdup(args);
//     }
//     size_t len = equals - args;
//     char *name = (char *)malloc(len + 1);
//     if (!name) {
//         return NULL;
//     }
//     strncpy(name, args, len);
//     name[len] = '\0';
//     return name;
// }

// int add_env_var(t_env **head, const char *key, const char *value) {
//     t_env *tmp = *head;
//     while (tmp) {
//         if (strcmp(tmp->name, key) == 0) {
//             free(tmp->value);
//             tmp->value = ft_strdup(value);
//             if (!tmp->value) {
//                 return 0;
//             }
//             return 1;
//         }
//         tmp = tmp->next;
//     }
//     t_env *new = (t_env *)malloc(sizeof(t_env));
//     if (!new) {
//         return 0;
//     }
//     new->name = ft_strdup(key);
//     new->value = ft_strdup(value);
//     if (!new->name || !new->value) {
//         free(new->name);
//         free(new->value);
//         free(new);
//         return 0;
//     }
//     new->next = *head;
//     *head = new;
//     return 1;
// }

// void ft_create_env(t_env **head, char **env) {
//     int i = 0;
//     while (env[i]) {
//         char *name = get_name(env[i]);
//         char *value = get_value(env[i]);
//         if (name && value) {
//             add_env_var(head, name, value);
//         }
//         free(name);
//         free(value);
//         i++;
//     }
// }

// void ft_print_env(t_env *head) {
//     t_env *tmp = head;
//     while (tmp) {
//         printf("%s=%s\n", tmp->name, tmp->value);
//         tmp = tmp->next;
//     }
// }

// void free_env_list(t_env *head) {
//     t_env *tmp;
//     while (head) {
//         tmp = head;
//         head = head->next;
//         free(tmp->name);
//         free(tmp->value);
//         free(tmp);
//     }
// }

// void ft_export(char **argv, char **env) {
//     t_env *env_list = NULL;
//     ft_create_env(&env_list, env);

//     int i = 1;
//     if (argv[i] == NULL) {
//         ft_print_env(env_list);
//     } else {
//         while (argv[i]) {
//             char *name = get_name(argv[i]);
//             char *value = get_value(argv[i]);
//             if (name && value) {
//                 add_env_var(&env_list, name, value);
//             }
//             free(name);
//             free(value);
//             i++;
//         }
//     }
//     free_env_list(env_list);
// }

// int main(int argc, char **argv, char **env) {
//     ft_export(argv, env);
//     return 0;
// }