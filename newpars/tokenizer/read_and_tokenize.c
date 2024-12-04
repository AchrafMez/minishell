/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_tokenize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 04:51:19 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/04 04:52:00 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
