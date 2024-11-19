#include "../minishell.h"

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
		if (strcmp(tmp->key, key) == 0)
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
	new->key = key;
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
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_export(t_env **env, char **argv)
{
	t_env *env_list;
	env_list = *env;


	int i = 1;

	if (argv[i] == NULL)
	{
		ft_print_env(&env_list);
		return;
	}

	while (argv[i])
	{
		char *name = get_name(argv[i]);
		char *value = get_value(argv[i]);
		add_env_var(&env_list, name, value);
		i++;
	}
		ft_print_env(&env_list);

	

}
