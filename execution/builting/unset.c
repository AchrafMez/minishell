#include"builtin.h"
static int	is_matching_env(t_env *env, char *name, int len)
{
	return (ft_strncmp(env->name, name, len + 1) == 0
		&& env->name[len] == '\0');
}

static void	free_env_node(t_env *node)
{

	free(node->name);
	node->value = NULL;
	node->name = NULL;

	free(node);
	node = NULL;
}

static void	remove_matching_nodes(t_env **env, char *name, int len)
{
	t_env	*prev;
	t_env	*current;

	prev = (*env);
	current = (*env)->next;
	if (!ft_strncmp((*env)->name, name, ft_strlen(name) + 1))
	{
		free_env_node(prev);
		(*env) = current;
		return ;
	}
	while (current != NULL)
	{
		if (is_matching_env(current, name, len))
		{
			prev->next = current->next;
			free_env_node(current);
			current = prev->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

static t_env	*remove_env_variable(char *name, t_env **env)
{
	int	len;

	if (name == NULL)
		return (NULL);
	len = ft_strlen(name);
	if (*env)
	{
		remove_matching_nodes(env, name, len);
	}
	return (*env);
}

t_env	*my_unset(char **name, t_env **env)
{
	int	i;

	i = 0;
	while (name[++i] != NULL)
		remove_env_variable(name[i], env);
	return (*env);
}