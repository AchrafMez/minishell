/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:55:25 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/26 18:36:22 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_space(char **cur, char *buffer, int *buf_idx,
		t_token **token_list)
{
	if (*buf_idx > 0)
	{
		buffer[*buf_idx] = '\0';
		add_token(token_list, create_token(buffer, WORD));
		*buf_idx = 0;
	}
	add_token(token_list, create_token(" ", SPACES));
	(*cur)++;
}

int	handle_pipe(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
	// if (!*token_list)
	// {
	// 	printf("syntax error near unexpected token '|'\n");
	// 	return (1);
	// }
	if (*buf_idx > 0)
	{
		buffer[*buf_idx] = '\0';
		add_token(token_list, create_token(buffer, WORD));
		*buf_idx = 0;
	}
	add_token(token_list, create_token("|", PIPE));
	(*cur)++;
	return (0);
}

int	handle_quotes(t_content *content)
{
	if (**content->cur == '"')
	{
		if (handle_double_quote(content) == 1)
			return (1);
	}
	else if (**content->cur == '\'')
	{
		if (handle_single_quote(content))
			return (1);
	}
	return (0);
}

int	handle_red(t_content *content)
{
	if (**content->cur == '>')
	{
		if (handle_red_out(content->cur, content->buffer, content->buf_idx,
				content->token_list) == 1)
			return (1);
	}
	else if (**content->cur == '<')
	{
		if (handle_red_in(content->cur, content->buffer, content->buf_idx,
				content->token_list) == 1)
			return (1);
	}
	return (0);
}
