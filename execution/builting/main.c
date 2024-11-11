
#include "builtin.h"

// void fork_builting(t_cmd *cmd, t_env **env)
// {
// 	pid_t pid;
// 	int status;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(cmd->path, cmd->args, NULL) == -1)
// 		{
// 			printf("Error: %s\n", strerror(errno));
// 			exit(1);
// 		}
// 	}
// 	else if (pid < 0)
// 	{
// 		printf("Error: %s\n", strerror(errno));
// 		exit(1);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// }
// int one_builting(t_cmd *cmd, t_env **env)
// {
// 	if (!cmd || !cmd->args || !cmd->args[0])
// 		return (0);
// 	if (!ft_strcmp(cmd->args[0], "cd"))
// 		return (cd_var(cmd->args[1], env));
// 	if (!ft_strcmp(cmd->args[0], "echo"))
// 	{
// 		ft_echo(cmd->args);
// 		return (1);
// 	}
// 	if (!ft_strcmp(cmd->args[0], "env"))
// 	{
// 		ft_env(*env, cmd->args);
// 		return (1);
// 	}
// 	if (!ft_strcmp(cmd->args[0], "exit"))
// 	{
// 		ft_exit(cmd->args);
// 		return (1);
// 	}
// 	if (!ft_strcmp(cmd->args[0], "export"))
// 	{
// 		*env = ft_export(cmd->args, *env);
// 		return (1);
// 	}
// 	if (!ft_strcmp(cmd->args[0], "pwd"))
// 	{
// 		ft_pwd(*env);
// 		return (1);
// 	}
// 	if (!ft_strcmp(cmd->args[0], "unset"))
// 	{
// 		ft_unset(env, cmd);
// 		return (1);
// 	}
// 	return (0);
// }

// void ft_execution(t_cmd **command, t_env ** env )
// {
// 	//initiall struct
// 	//5asni heredoc
// 	//check if its builting
// 	//execv
// 	if(!cmd || !*cmd)
// 		return;
// 	process_heredocs(command, env);
// 	while(command->next)
// 	{
// 		if(one_builting(*command, env))
// 			return;
// 		fork_builting(*command, env);
// 		command = command->next;

// 	}
	

// }
t_exer g_glb;
int	ft_strcmp(const char *s1, char *s2)
{
	int	i;

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
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
static int	nbrarray(char const *s, char c)
{
	int	i;
	int	j;
	int	nbrstr;

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
	int	l;

	l = 0;
	while (str[l])
	{
		free(str[l++]);
	}
	return ;
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	l;
	char			*str;

	i = 0;
	l = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		str = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	else
		str = (char *) malloc((len + 1) * sizeof(char));
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
	int	i;
	int	j;
	int	l;

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
	char	**str;
	int		i;

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
int	size_env(t_env	**env)
{
	t_env	*tmp;
	int		cnt;

	if (!env)
		return (0);
	cnt = 0;
	tmp = *env;
	while (tmp)
	{
		if (tmp->dx == 2 || tmp->dx == 0)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		j;
	int		i;

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
void	Tslash(char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		i++;
	}
}


char	**env_to_envp(t_env **env)
{
	char	**envp;
	t_env	*tmp;
	char	*fr;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	envp = malloc(sizeof(char *) * (size_env(env) + 1));
	tmp = *env;
	while (tmp)
	{
		if (tmp->dx == 2 || tmp->dx == 0)
		{
			fr = ft_strjoin(tmp->key, "=");
			envp[i] = ft_strjoin(fr, tmp->value);
			free(fr);
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = 0;
	return (envp);
}	
t_env	*getEnvarement(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	allocptr(t_extra *ptr, t_env **tmp, t_env **env)
{
	t_env	*mis;

	*tmp = getEnvarement(env, "PATH");
	mis = *tmp;
	ptr->envp = env_to_envp(env);
	if (mis)
	{
		ptr->path = ft_split(mis->value, ':');
		Tslash(ptr->path);
	}
	ptr->pid = malloc(sizeof(int) * (ptr->size + 1));
}
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

int	ft_size_list(t_cmd *list)
{
	int			cnt;
	t_cmd	*tmp;

	tmp = list;
	cnt = 0;
	while (tmp)
	{
		cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

// env part
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
	t_env	*lst;

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
	size_t	i;
	char	*ptr_d;
	char	*ptr_s;

	i = 0;
	ptr_d = (char *) dest;
	ptr_s = (char *) src;
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
	char	*str;

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
	int		i;
	char	**str;
	int		len;

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

void	handle_exec(char **path, t_cmd	*list, t_env **env, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	// if (there_is_slash(list->command[0]))
	// 	slash_exec(list->command, envp);
	// else
	// {
		while (getEnvarement(env, "PATH") && path[i])
		{
			tmp = ft_strjoin(path[i], list->args[0]);
			if (execve(tmp, list->args, envp) == -1)
			{
				i++;
				free(tmp);
			}
		}
	// }
	//command_not_found(list->command, ": command not found\n", 127);
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
void	condition_dup(t_extra ptr)
{
	if (ptr.i != ptr.size)
		dup2(ptr.tube[ptr.i][1], 1);
}
int	assining_out(t_red *tmp, int	*fd)
{
	if (tmp->type == RED_OUT)
		*fd = open(tmp->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	// else if (tmp->type == RED_APP)
	// 	*fd = open(tmp->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror("ERROR");
		return (0);
	}
	return (1);
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


void	handle_child(t_cmd	*cmd, t_env **env, t_extra ptr)
{
	// signal(SIGQUIT, SIG_DFL);
	// signal(SIGINT, SIG_DFL);
	input_cmd(cmd->red, ptr, cmd->args);
	output_cmd(cmd->red_out, ptr);
	closingB(ptr.tube, ptr.size);
	if (cmd->args)
		handle_exec(ptr.path, cmd, env, ptr.envp);
	else
		exit (0);
}
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_wait(t_extra ptr)
{
	int	i;
	int	status;

	free_tab(ptr.path);
	free_tab(ptr.envp);
	closingB(ptr.tube, ptr.size);
	i = 0;
	while (i <= ptr.size)
	{
		waitpid(ptr.pid[i], &status, 0);
		if (WIFSIGNALED(status))
			g_glb.ex = 128 + WTERMSIG(status);
		else
			g_glb.ex = WEXITSTATUS(status);
		i++;
	}
	free(ptr.pid);
}

//..........................................................
void	execution(t_cmd **list, t_env **env)
{
	t_extra		ptr;
	t_cmd	*cmd;
	t_env		*tmp;


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

int main(int argc, char **argv, char **environ)
{
	
	t_cmd	*list;
	t_env		*env;

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