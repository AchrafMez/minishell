
#include "builtin.h"

int	**prc_allocation(int size)
{
	int i;
	int **tube;

	i = 0;
	tube = malloc(sizeof(int *) * size);
	if (!tube)
		return (NULL);
	while (i < size)
	{
		tube[i] = malloc(sizeof(int) * 2);
		if (!tube[i])
			return (NULL);
		i++;
	}
	return (tube);
}

void	check_Opwd(char **str)
{
	if (ft_strcmp(str[0], "OLDPWD"))
	{
		free(str[1]);
		str[1] = ft_strdup("");
	}
}

t_env	*get_env(char **env)
{
	char **str;
	int i;
	t_env *envp;
	t_env *tmp;

	i = 0;
	str = NULL;
	envp = 0;
	while (env[i])
	{
		str = ft_strplit(env[i]);
		check_Opwd(str);
		tmp = ft_lstnew_env(str[0], str[1]);
		if (ft_strcmp(tmp->key, "_"))
			tmp->dx = 0;
		else
			tmp->dx = 2;
		ft_lstadd_back_env(&envp, tmp);
		free(str);
		i++;
	}
	return (envp);
}
void	execution(t_cmd **list, t_env **env)
{
	t_extra ptr;
	t_cmd *cmd;
	t_env *tmp;

	cmd = *list;
	ptr.i = 0;
	ptr.size = ft_size_list(*list) - 1;
	ptr.tube = prc_allocation(ptr.size);
	if (!ptr.tube)
		return ;
	allocptr(&ptr, &tmp, env);
	while (ptr.i <= ptr.size)
	{
		ptr.pid[ptr.i] = fork();
		if (!ptr.pid[ptr.i])
			handle_child(cmd, env, ptr);
		ptr.i++;
		cmd = cmd->next;
	}
	ft_free_wait(ptr);
}

int	main(int argc, char **argv, char **environ)
{
	t_cmd *list;
	t_env *env;

	list = malloc(sizeof(t_cmd));
	list->args = malloc(2 * sizeof(char *));
	list->args[0] = ft_strdup("ls");

	list->red = malloc(sizeof(t_red));
	list->red->value = ft_strdup("test.txt");
	list->red->type = RED_IN;
	list->red->next = NULL;

	list->red_out = malloc(sizeof(t_red));
	list->red_out->value = ft_strdup("tst.txt");
	list->red_out->type = RED_OUT;
	list->red_out->next = NULL;

	list->next = NULL;
	env = get_env(environ);
	execution(&list, &env);
	return (0);
}
