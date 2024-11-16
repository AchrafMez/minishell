/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:52:13 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/14 11:05:48 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_red(t_red **red_list, char *value, t_token_type type)
{
	t_red	*new_red;
	t_red	*cur;

	new_red = malloc(sizeof(t_red));
	new_red->value = strdup(value);
	new_red->type = type;
	new_red->next = NULL;
	if (*red_list == NULL)
	{
		*red_list = new_red;
		return ;
	}
	cur = *red_list;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = new_red;
}

void	add_arg(char ***args, int *arg_count, char *value)
{
	int		i;
	int		count;
	char	**new_args;

	count = 0;
	i = 0;
	while ((*args)[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	while (i < count)
	{
		new_args[i] = (*args)[i];
		i++;
	}
	new_args[count] = strdup(value);
	new_args[count + 1] = NULL;
	free(*args);
	*args = new_args;
	(*arg_count)++;
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->name = NULL;
	cmd->args = malloc(sizeof(char *));
	cmd->args[0] = NULL;
	cmd->path = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->next = NULL;
	return (cmd);
}
