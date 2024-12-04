/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:43:55 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/04 00:56:49 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	write_to_file(char *limiter_newline, int fd, t_env *env)
{
	char	*line;
	int		i;

	while (1)
	{
		write(1, "--> ", 4);
		line = get_next_line(0);
		if (!line)
		{
			free(limiter_newline);
			break ;
		}
		if (ft_strncmpp(line, limiter_newline, ft_strlen(limiter_newline)) == 0)
		{
			free(line);
			free(limiter_newline);
			break ;
		}
		i = 0;
		i = help_heredoc(line, i, fd, env);
		free(line);
	}
	return (fd);
}

void	herdoc_sig(int sig)
{
	(void)sig;
	exit(1);
}

static int	write_to_heredoc_file(int fd, char *limiter, t_env *env)
{
	char	*limiter_newline;

	signal(SIGINT, herdoc_sig);
	if (limiter[0] == '\0')
	{
		limiter_newline = ft_strjoin(NULL, "\n");
	}
	else
		limiter_newline = ft_strjoin(limiter, "\n");
	if (!limiter_newline)
		ft_error("ft_strjoin", 1, 0);
	fd = write_to_file(limiter_newline, fd, env);
	close(fd);
	open("/tmp/heredoc", O_RDONLY);
	exit(0);
}

int	handle_here_doc(char *limiter, t_env *env)
{
	int		fd;
	pid_t	pid;

	fd = -1;
	pid = fork();
	fd = open("/tmp/heredocx", O_RDWR | O_CREAT | O_TRUNC, 0774);
	if (fd == -1)
		ft_error("open", 1, 0);
	if (pid == 0)
		write_to_heredoc_file(fd, limiter, env);
	else
		waitpid(pid, &g_glb.ex, 0);
	return (fd);
}

void	get_herdoc(t_command **p_cmd, t_env *env)
{
	t_command	*tmp;
	t_red		*in;

	tmp = *p_cmd;
	tmp->fd = -1;
	while (tmp)
	{
		in = tmp->in;
		tmp->fd = -1;
		while (in)
		{
			if (in->type == HERE_DOC)
				tmp->fd = handle_here_doc(in->value, env);
			in = in->next;
		}
		tmp = tmp->next;
	}
}
