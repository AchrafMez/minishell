#include "builtin.h"


void	process_heredoc(const char *delimiter, t_env *env);
static void	process_heredocs(t_cmd *cmd, t_env *env);
char	*readline(const char *prompt);

int	main(void)
{
	t_env env;
	t_cmd cmd;

	env.key = NULL;
	env.value = NULL;
	cmd.red = malloc(sizeof(t_red));
	if (!cmd.red)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd.red->type = HERE_DOC;
	printf("1\n");
	cmd.args = malloc(2 * sizeof(char *));
	if (!cmd.args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd.args[0] = "heredoc";
	cmd.args[1] = "END";
	cmd.next = NULL;

	process_heredocs(&cmd, &env);

	free(cmd.args);
	return (0);
}

void	process_heredoc(const char *delimiter, t_env *env)
{
	char *line;
	int tmp_fd;
	char tmp_filename[] = "/tmp/heredoc.txt";

	tmp_fd = open(tmp_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	// printf("Heredoc saved in: %s\n", tmp_filename);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			free(line);
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open(tmp_filename, O_RDONLY);
	if (tmp_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	if (dup2(tmp_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}

	close(tmp_fd);
}

static void	process_heredocs(t_cmd *cmd, t_env *env)
{
	t_cmd *curr = cmd;

	while (curr != NULL)
	{
		if (curr->red->type == HERE_DOC)
		{
			process_heredoc(curr->args[1], env);
		}
		curr = curr->next;
	}
}

// Simulated readline function
char	*readline(const char *prompt)
{
	char *line = NULL;
	size_t len = 0;
	printf("%s", prompt);
	getline(&line, &len, stdin);
	line[strcspn(line, "\n")] = 0;
	return (line);
}