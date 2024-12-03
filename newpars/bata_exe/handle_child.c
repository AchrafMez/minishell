/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:44:17 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/03 07:21:41 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if ((tmp->type == RED_OUT || tmp->type == RED_APP) && assining_out(tmp,
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
			{
				exit(1);
				}
					printf("fd = %d\n", fd);
	set_export_env(ptr.env, "?", "999");
		tmp = tmp->next;
	}
}

void	assaining_in(t_red *tmp, int fd, t_env **env)
{
	(void)env;
	if (fd == -2)
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

void	input_cmd(t_red *in, t_extra ptr, char **cmd, int fd, t_env **env)
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
			assaining_in(tmp, -2, env);
		else if (tmp->type == HERE_DOC && !tmp->next)
			assaining_in(tmp, fd, env);
		// 	read_herdoc(cmd, tmp);
		tmp = tmp->next;
	}
}

void	handle_child(t_command *cmd, t_env **env, t_extra ptr)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	input_cmd(cmd->in, ptr, cmd->args, cmd->fd, env);
	output_cmd(cmd->out, ptr);
	closingb(ptr.tube, ptr.size);
	if (cmd->args)
		handle_exec(ptr.path, cmd, env, ptr.envp);
	else
		exit(0);
}
