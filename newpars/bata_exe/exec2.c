/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/12/02 18:42:52 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/02 18:42:52 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_red			*tmp;
	int				fd;
	int				ret;

	tmp = out;
	ret = 0;
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
