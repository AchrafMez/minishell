/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:43:55 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/03 06:53:37 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *message, int exit_code, int f)
{
	g_glb.ex = exit_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (f == 0)
		exit(g_glb.ex);
}

int	ft_strncmpp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (s1[i] != '\0' || s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_chr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}

void	ft_dollar(char *str, int *i, int fd, t_env *env)
{
	char	*s;
	int		j;
	char	*val;

	*i = *i + 1;
	j = *i;
	val = NULL;
	
	while ((str[*i] >= '0' && str[*i] <= '9') || ft_isalpha(str[*i]))
		*i = *i + 1;
	if (str[j] == '_')
		*i = *i + 1;
	s = ft_substr(str, j, *i - j);
	while (env)
	{
		val = get_env_value(env, s);
		if (val)
		{
			write(fd, val, ft_strlen(val));
			break ;
		}
		env = env->next;
	}
	free(s);
	*i = *i - 1;
}

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
		while (line[i])
		{
			if (line[i] == '$' && line[i + 1] >= '0' && line[i + 1] <= '9')
				i += 2;
			else if (line[i] == '$')
				ft_dollar(line, &i, fd, env);
			else
				write(fd, line + i, 1);
			i++;
		}
		// write(fd, "\n", 1);
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
