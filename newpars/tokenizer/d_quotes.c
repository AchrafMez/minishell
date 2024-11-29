/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:48:16 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/27 18:26:34 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_double_quote_helper(t_content *content)
{
	(*content->cur)++;
	while (**content->cur && **content->cur != ' ' && **content->cur != '|')
	{
		if (**content->cur == '$')
			handle_dollar(content, 0);
		else if (**content->cur == '\'')
		{
			(*content->cur)++;
			while (**content->cur && **content->cur != '\'')
				content->buffer[(*content->buf_idx)++] = *(*content->cur)++;
			if (**content->cur == '\'')
				(*content->cur)++;
		}
		else if (**content->cur == '\"')
			handle_double_quote(content);
		else
			content->buffer[(*content->buf_idx)++] = *(*content->cur)++;
	}
}

int	handle_double_quote(t_content *content)
{
	(*content->cur)++;
	while (**content->cur && **content->cur != '"')
	{
		if (**content->cur == '$' && (**content->cur) + 1 == '?')
			handle_dollar(content, 0);
		else if (**content->cur == '$')
			handle_dollar(content, 0);
		else
			content->buffer[(*content->buf_idx)++] = *(*content->cur)++;
	}
	if (**content->cur == '\0')
	{
		printf("Error -> unclosed double quotes\n");
		return (1);
	}
	handle_double_quote_helper(content);
	content->buffer[*content->buf_idx] = '\0';
	add_token(content->token_list, create_token(content->buffer, D_QUOTE));
	*content->buf_idx = 0;
	return (0);
}
