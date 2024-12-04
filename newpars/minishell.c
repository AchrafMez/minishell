/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:13:12 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 04:51:31 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	main_process(t_env **env, t_token *token_list)
{
	t_command	*cmd;

	cmd = NULL;
	if (token_list)
	{
		cmd = fill_command(token_list, *env);
		if (cmd)
		{
			set_path(&cmd);
			execution(&cmd, env);
			free_cmd(cmd);
			cmd = NULL;
		}
	}
}

void	main_loop(t_env **env)
{
	t_token	*token_list;

	token_list = NULL;
	while (1)
	{
		read_and_tokenize(env, &token_list);
		{
			if (token_list)
			{
				main_process(env, token_list);
				ft_tokens_free(token_list);
				token_list = NULL;
			}
		}
	}
}
