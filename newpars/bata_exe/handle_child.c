#include"../minishell.h"

void	command_not_found(char **arg, char *mes, int ret)
{
	write(2, arg[0], ft_strlen(arg[0]));
	write(2, mes, ft_strlen(mes));
	exit(ret);
}
void	slash_exec(char **arg, char **envp)
{
	struct stat	m;

	if (stat(arg[0], &m) == -1)
		return ;
	if (S_ISDIR(m.st_mode))
		command_not_found(arg, ": is a directory\n", 126);
	else if (access(arg[0], X_OK) == -1)
		command_not_found(arg, ": Permission denied\n", 126);
	execve(arg[0], arg, envp);
}
int	there_is_slash(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
void	handle_exec(char **path, t_command	*list, t_env **env, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	if (there_is_slash(list->args[0]))
		slash_exec(list->args, envp);

	if (is_builting(list))
	{
		free_tab(envp);
		// exec_builtins(list, env);
		exit(g_glb.ex);
	}
	else
	{	
		while (getEnvarement(env, "PATH") && path[i])
		{
			tmp = ft_strjoin(path[i], list->args[0]);
			if (execve(tmp, list->args, envp) == -1)
			{
				i++;
				free(tmp);
			} 
		}
	}
	command_not_found(list->args, ": command not found\n", 127);
}
int	closingB(int **tube, int pos)
{
	while (pos > 0)
	{
		close(tube[pos - 1][0]);
		close(tube[pos - 1][1]);
		free(tube[pos - 1]);
		pos--;
	}
	free(tube);
	return (0);
}
int	assining_out(t_red *tmp, int	*fd)
{
	if (tmp->type == RED_OUT)
		*fd = open(tmp->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (tmp->type == RED_APP)
		*fd = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror("ERROR");
		return (0);
	}
	return (1);
}
void	condition_dup(t_extra ptr)
{
	if (ptr.i != ptr.size)
		dup2(ptr.tube[ptr.i][1], 1);
}
void	output_cmd(t_red *out, t_extra ptr)
{
	t_red	*tmp;
	int		fd;

	tmp = out;
	if (!out)
	{
		condition_dup(ptr);
		return ;
	}
	while (tmp)
	{
		if ((tmp->type == RED_OUT /*tmp->type == OUTP*/) && assining_out(tmp, &fd))
		{
			if (tmp->next)
				close(fd);
			else
			{
				dup2(fd, 1);
				close(fd);
			}
		}
		else
			exit(1);
		tmp = tmp->next;
	}
}
void	assaining_in(t_red *tmp)
{
	int	fd;

	fd = open(tmp->value, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		exit(1);
	}
	if (tmp->next)
		close(fd);
	else
		dup2(fd, 0);
}
void	input_cmd(t_red *in, t_extra ptr, char **cmd)
{
	t_red	*tmp;
	(void)cmd;
	tmp = in;
	if (!in)
	{
		if (ptr.i != 0)
			dup2(ptr.tube[ptr.i - 1][0], 0);
		return ;
	}
	while (tmp)
	{
		if (tmp->type == RED_IN)
			assaining_in(tmp);
		// else if (tmp->type == HERDOC && !tmp->next)
		// 	read_herdoc(cmd, tmp);
		tmp = tmp->next;
	}
}
void	handle_child(t_command	*cmd, t_env **env, t_extra ptr)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	input_cmd(cmd->in, ptr, cmd->args);
	output_cmd(cmd->out, ptr); 
	closingB(ptr.tube, ptr.size);
	if (cmd->args)
		handle_exec(ptr.path, cmd, env, ptr.envp);
	else
		exit (0);
}