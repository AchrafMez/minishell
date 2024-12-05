/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:48:18 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/04 04:13:09 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *message, int exit_code, int f)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (f == 0)
		exit(exit_code);
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

int	help_heredoc(char *line, int i, int fd, t_env *env)
{
	char	*s;

	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			s = get_env_value(env, "?");
			write(fd, s, ft_strlen(s));
			free(s);
			i += 2;
		}
		if (line[i] == '$' && line[i + 1] >= '0' && line[i + 1] <= '9')
			i += 2;
		else if (line[i] == '$')
			ft_dollar(line, &i, fd, env);
		else
			write(fd, line + i, 1);
		i++;
	}
	return (i);
}
