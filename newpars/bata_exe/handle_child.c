#include "../minishell.h"

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
int there_is_slash(char *arg) {
    int i;

    i = 0;
    // if (arg[0] == '.' && arg[1] == '/')
    //     return (1);
    while (arg[i]) {
        if (arg[i] == '/')
            return (1);
        i++;
    }
    return (0);
}
void	handle_exec(char **path, t_command *list, t_env **env, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;

	// printf("list->args[0] = %s\n", list->args[0]);
	if (list->args[0] && there_is_slash(list->args[0]))
        slash_exec(list->args, envp);
	if (is_builting(list))
	{
		// printf("built in\n");
		free_tab(envp);
		exec_builtins(list, env);
		update_exit_value(env, g_glb.ex);
		exit(g_glb.ex);
	}
	else
	{
		// print env
		// printf("=>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>envp\n");
		// t_env	*tmp55= *env;
		// for (int i = 0; tmp55; i++)
		// {
		// 	printf("env[%d] = %s\n", i, tmp55->key);
		// 	tmp55 = tmp55->next;
		// }
		while (getEnvarement(env, "PATH") && path[i])
		{
	// printf("====================================\n");
	// tmp = "/bin/ls";
			tmp = ft_strjoin(path[i], list->args[0]);
			// printf("tmp = %s list->command %s   \n", tmp, list->args[0]);
			if (execve(tmp, list->args, envp) == -1)
			{
				i++;
				free(tmp);
			}
		}
	}
	// printf("handle exec\n");
	update_exit_value(env, 127);
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
int	assining_out(t_red *tmp, int *fd)
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
		if ((tmp->type == RED_OUT  || tmp->type == RED_APP) && assining_out(tmp,
				&fd))
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



//------------------------------------------------------------------------------------------------------------------------------------


void cleanup_heredocs(t_red *red)
{
    // In case the file was created for heredoc input, remove it
    if (red->fd_in != -1)
    {
        close(red->fd_in);  // Close the file descriptor
        red->fd_in = -1;    // Reset the fd to avoid reusing it
        unlink(red->value); // Remove the temporary heredoc file
    }
}

void execute_command(t_command *cmd)
{
    t_red *red = cmd->in;  // Start with the input redirection list

    // Handle input redirection (including heredoc)
    while (red)
    {
        if (red->type == HERE_DOC)
        {
            // Redirect input to the heredoc file
            dup2(red->fd_in, STDIN_FILENO);
            close(red->fd_in);  // Close the fd after using it
        }
        red = red->next;
    }

    // Execute the command (after redirection)
    if (execve(cmd->path, cmd->args, NULL) == -1)
    {
        perror("execve");
        exit(1);
    }
}






void handle_herdc_inp(t_red *red)
{
    int fd;
    char *line;
    char *delimiter = red->value;  // The delimiter for the heredoc (e.g., 'EOF')

    // Create a unique temporary filename for the heredoc content
    char *tmp_file = malloc(256);
    if (!tmp_file)
    {
        perror("malloc");
        exit(1);
    }
    snprintf(tmp_file, 256, "/tmp/heredoc_%ld.tmp", time(NULL));

    // Open the temporary file for writing
    fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        free(tmp_file);
        exit(1);
    }

    // Read input until the delimiter is encountered
    while (1)
    {
        line = readline("> ");  // Prompt for user input
        if (!line) break;  // Handle EOF or Ctrl-D

        // If the input is the delimiter, stop reading
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }

        // Write the line to the temporary file
        write(fd, line, strlen(line));
        write(fd, "\n", 1);  // Add a newline after each line

        free(line);  // Free the line after processing
    }

    close(fd);  // Close the file after writing

    // Update the redirection struct to point to the temporary file
    red->fd_in = open(tmp_file, O_RDONLY);  // Open the file for reading
    if (red->fd_in < 0)
    {
        perror("open");
        free(tmp_file);
        exit(1);
    }

    free(tmp_file);  // Clean up the temporary file path
}

void process_heredocs(t_command *cmd)
{
    t_red *red = cmd->in;  // Start with the input redirection list

    // Iterate through each redirection to find heredocs
    while (red)
    {
        if (red->type == HERE_DOC)  // If this is a heredoc redirection
        {
            handle_herdc_inp(red);  // Handle the heredoc input
        }
        red = red->next;  // Move to the next redirection
    }
}
// void execute_command(t_command *cmd)
// {
//     t_red *red = cmd->in;  // Start with the input redirection list

//     // Handle input redirection (including heredoc)
//     while (red)
//     {
//         if (red->type == HEREDOC)
//         {
//             // Redirect input to the heredoc file
//             dup2(red->fd_in, STDIN_FILENO);
//             close(red->fd_in);  // Close the fd after using it
//         }
//         red = red->next;
//     }

//     // Execute the command (after redirection)
//     if (execve(cmd->path, cmd->args, NULL) == -1)
//     {
//         perror("execve");
//         exit(1);
//     }
// }






void	input_cmd(t_red *in, t_extra ptr, char **cmd, t_env **env)
{
	t_red	*tmp;

	(void)cmd;
	(void)env;
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
		// else if (tmp->type == HERE_DOC && !tmp->next)
		// 	handle_herdc_inp(tmp);
		tmp = tmp->next;
	}
}
void	handle_child(t_command *cmd, t_env **env, t_extra ptr)
{

	// signal(SIGQUIT, SIG_DFL);
	// signal(SIGINT, SIG_DFL);
	input_cmd(cmd->in, ptr, cmd->args, env);
	output_cmd(cmd->out, ptr);
	closingB(ptr.tube, ptr.size);
	if (cmd->args)
		handle_exec(ptr.path, cmd, env, ptr.envp);
	else
		exit(0);
}