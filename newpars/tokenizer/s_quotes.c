/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:15:25 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/12 11:15:35 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_single(char **cur, char *buffer, int *buf_idx)
{
	(*cur)++;
	while (**cur && **cur != '\'')
		buffer[(*buf_idx)++] = *(*cur)++;
	if (**cur == '\0')
	{
		printf("Error -> unclosed single quote\n");
		return (1);
	}
	return (0);
}

void	check_single_for_helper(t_content *content)
{
	(*content->cur)++;
	while (**content->cur && **content->cur != '\"')
	{
		if (**content->cur == '$')
			handle_dollar(content, 0);
		else
			content->buffer[(*content->buf_idx)++] = *(*content->cur)++;
	}
}

int	handle_singlequote_helper(t_content *content)
{
	while (**content->cur && **content->cur != ' ' && **content->cur != '|')
	{
		if (**content->cur == '$')
			handle_dollar(content, 0);
		else if (**content->cur == '\'')
		{
			if (handle_single_quote(content))
				return (1);
		}
		else if (**content->cur == '\"')
		{
			check_single_for_helper(content);
			if (**content->cur == '\0')
			{
				printf("Error -> unclosed double quote\n");
				return (1);
			}
			(*content->cur)++;
		}
		else
			content->buffer[(*content->buf_idx)++] = *(*content->cur)++;
	}
	return (0);
}

int	handle_single_quote(t_content *content)
{
	if (check_single(content->cur, content->buffer, content->buf_idx) == 1)
		return (1);
	(*content->cur)++;
	if (handle_singlequote_helper(content) == 1)
		return (1);
	content->buffer[*content->buf_idx] = '\0';
	add_token(content->token_list, create_token(content->buffer, S_QUOTE));
	*content->buf_idx = 0;
	return (0);
}
