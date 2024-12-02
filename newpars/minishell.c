/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:13:12 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/02 23:33:52 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

char	*skip_spaces(char *input)
{
	while (*input == ' ')
		input++;
	return (input);
}
void	r_t_assit(char *input, t_env **env)
{
	if (!input)
		exit(0);
	input = skip_spaces(input);
	if (*input == '\0')
		return ;
	if (check_unclosed_quotes(input))
	{
		set_export_env(env, "?", "258");
		add_history(input);
		return ;
	}
	if (ft_strlen(input) > 0)
		add_history(input);
}
void	read_and_tokenize(t_env **env, t_token **token_list)
{
	int		res;
	char	*input;

	input = NULL;
	input = readline("minishell$ ");
	r_t_assit(input, env);
	if (!input || *input == '\0' || check_unclosed_quotes(input))
		return ;
	*token_list = tokenize_input(input, env);
	if (*token_list)
		tokens_edit(token_list);
	else
		return ;
	res = check_syntax(*token_list);
	if (res == 258)
	{
		set_export_env(env, "?", "258");
		ft_tokens_free(*token_list);
		*token_list = NULL;
	}
	free(input);
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
		// system("leaks minishell");
		// atexit(leaks);
	}
}

void	update_exit_value(t_env **env, int status)
{
	char	*value;

	value = ft_itoa(status);
	set_env_value(env, "?", value);
	free(value);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	env = NULL;
	env = convert_env(envp);
	set_export_env(&env, "?", "0");
	handle_signals();
	if (ac == 1)
		main_loop(&env);
	return (0);
}
