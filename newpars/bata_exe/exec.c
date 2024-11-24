#include "../minishell.h"

int	**prc_allocation(int size)
{
	int	i;
	int	**tube;

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
	char	**str;
	int		i;
	t_env	*envp;
	t_env	*tmp;

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
int	is_builting(t_command *cmd)
{
	// if (!ft_strcmp(cmd->args[0], "cd") || !ft_strcmp(cmd->args[0], "pwd")
	// 	|| !ft_strcmp(cmd->args[0], "export") || !ft_strcmp(cmd->args[0], "unset")
	// 	|| !ft_strcmp(cmd->args[0], "env") || !ft_strcmp(cmd->args[0], "exit"))
	// 	return (1);
	// return (0);
	if(ft_strcmp(cmd->name, "cd") == 0)
		return (1);
	else if(ft_strcmp(cmd->name, "pwd")== 0)
		return (1);
	else if(ft_strcmp(cmd->name, "export")== 0)
		return (1);
	else if(ft_strcmp(cmd->name, "unset")== 0)
		return (1);
	else if(ft_strcmp(cmd->name, "env")== 0)
		return (1);
	else if(ft_strcmp(cmd->name, "exit")== 0)
		return (1);
	return (0);
}
int	input_builtins(t_red *in)
{
	t_red	*tmp;

	tmp = in;
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (tmp->type == RED_IN && access(tmp->value, R_OK) == -1)
		{
			perror("ERROR");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
int	out_fd_assign(t_red *tmp, int *fd)
{
	if (tmp->type == RED_OUT)
		*fd = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->type == RED_APP)
		*fd = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror("ERROR");
		return (0);
	}
	return (1);
}
void	duplicate_fd(int *ret, int fd)
{
	*ret = dup(1);
	dup2(fd, 1);
	close(fd);
}
int	output_builtins(t_red *out)
{
	t_red	*tmp;
	int		fd;
	int		ret;

	ret = 0;
	tmp = out;
	if (!tmp)
		return (-2);
	while (tmp)
	{	
		if ((tmp->type == RED_OUT || tmp->type == RED_APP) && out_fd_assign(tmp,
				&fd))
		{
			if (tmp->next)
				close(fd);
			else
				duplicate_fd(&ret, fd);
		}
		else
			return (-1);
		tmp = tmp->next;
	}
	return (ret);
}
int	open_files(int *fd, t_command *cmd)
{
		

	if (!input_builtins(cmd->in))
	{
		g_glb.ex = 1;
		return (0);
	}
	*fd = output_builtins(cmd->out);
	if (*fd == -1)
	{
		g_glb.ex = 1;
		return (0);
	}
	return (1);
}
void	exec_builtins(t_command *cmd, t_env **env)
{
	int	fd;

	if (!open_files(&fd, cmd))
		return ;
	if (ft_strcmp(cmd->name, "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->name, "cd") == 0)
		cd(cmd->args, *env);
	else if (ft_strcmp(cmd->name, "env") == 0)
		ft_env(cmd->args, *env);
	else if (ft_strcmp(cmd->name, "export") == 0)
		export(cmd->args, env);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		echo(cmd->args);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		unset(cmd->args, env);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		ft_exit(cmd->args, 0);
	if (fd != -2)
	{
		dup2(fd, 1);
		close(fd);
	}
}
int	**alloc_tube(int size)
{
	int	**tube;
	int	i;

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
int	open_pipes(int **tube, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pipe(tube[i]) == -1)
			return (closingB(tube, i));
		i++;
	}
	return (1);
}
int	**builtins_tube(t_command **list, t_env **env, int size)
{
	int			**tube;
	t_command	*cmd;	
	// printf("******************************r>??**************zbi********************************************\n");

	cmd = *list;
	if (size == 0 && cmd->args && is_builting(cmd))
	{
		exec_builtins(cmd, env);
		return (NULL);
	}
	tube = alloc_tube(size);
	if (!open_pipes(tube, size) || !tube)
	{
		write(2, "ERROR : open_pipe ou allocation\n", 32);
		g_glb.ex = -1;
		closingB(tube, size);
		return (NULL);
	}
	return (tube);
}
void	execution(t_command **list, t_env **env)
{
	t_extra		ptr;
	t_command	*cmd;
	t_env		*tmp;
	

	cmd = *list;
	ptr.i = 0;
	ptr.size = ft_size_list(*list) - 1;

	ptr.tube = builtins_tube(list, env, ptr.size);
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

