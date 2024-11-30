/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:35:56 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/30 04:55:19 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenize_helper(t_content *content)
{
	if (**content->cur == '"' || **content->cur == '\'')
	{
		if (handle_quotes(content) == 1)
			return (1);
	}
	else if (**content->cur == '|')
	{
		if (handle_pipe(content->cur, content->buffer, content->buf_idx,
				content->token_list) == 1)
			return (1);
	}
	else if (**content->cur == '<' || **content->cur == '>')
	{
		if (handle_red(content) == 1)
			return (1);
	}
	else if (**content->cur == '$')
		handle_dollar(content, 0);
	else
		content->buffer[(*content->buf_idx)++] = *(*content->cur)++;
	return (0);
}

int	test(t_content *content)
{
	while ((**content->cur))
	{
		if ((**content->cur) == ' ')
			handle_space(content->cur, content->buffer, content->buf_idx,
				content->token_list);
		else if ((**content->cur) || (**content->cur) == '|'
			|| (**content->cur) == '>' || (**content->cur) == '<'
			|| (**content->cur) == '$' || (**content->cur) == '"'
			|| (**content->cur) == '\'')
		{
			if (tokenize_helper(content) == 1)
			{
				set_export_env(&content->env, "?", "258");
				ft_tokens_free(*(content->token_list));
				return (1);
			}
		}
	}
	return (0);
}

t_token	*tokenize_input(char *input, t_env **env)
{
	t_token		*token_list;
	char		*cur;
	// char		buffer[1024000];
	int res = ft_strlen(input);
	char *buffer = malloc(res + 1);
	if(!buffer)
		return (NULL);
	buffer[res] = '\0';
	int			buf_idx;
	t_content	content;

	buf_idx = 0;
	token_list = NULL;
	cur = input;

	content.cur = &cur;
	content.buffer = buffer;
	content.buf_idx = &buf_idx;
	content.token_list = &token_list;
	content.env = *env;

	if (test(&content) == 1) 
	{
		free(buffer);	
		return (NULL);
	}

	if (buf_idx > 0) 
	{
		buffer[buf_idx] = '\0';
		add_token(&token_list, create_token(buffer, WORD));
	}
	free(buffer);
	return (token_list);
}
