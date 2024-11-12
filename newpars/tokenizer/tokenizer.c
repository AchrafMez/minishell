/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:35:56 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/12 12:41:24 by amezioun         ###   ########.fr       */
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
	if (!*token_list)
	{
		printf("syntax error near unexpected token '|'\n");
		return (1);
	}
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

void	handle_dollar(t_content *content, int flag)
{
	char	key[256];
	int		key_idx;
	char	*expanded;
	int		i;

	(*content->cur)++;
	key_idx = 0;
	while (**content->cur && (ft_isalnum(**content->cur)
			|| **content->cur == '_'))
		key[key_idx++] = *(*content->cur)++;
	key[key_idx] = '\0';
	expanded = get_env_value(content->env, key);
	i = 0;
	if (expanded)
	{
		while (expanded[i] != '\0')
			content->buffer[(*content->buf_idx)++] = expanded[i++];
		if (flag == 1)
		{
			add_token(content->token_list, create_token(expanded, ENV));
			*content->buf_idx = 0;
		}
	}
	else
	{
		i = 0;
		content->buffer[(*content->buf_idx)] = '$';
		while (key[i] != '\0')
			content->buffer[(*content->buf_idx)++] = key[i++];
		if (flag == 1)
		{
			add_token(content->token_list, create_token(content->buffer, WORD));
			*content->buf_idx = 0;
		}
	}
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
		handle_dollar(content, 1);
	else
		content->buffer[(*content->buf_idx)++] = *(*content->cur)++;
	return (0);
}
t_token *tokenize_input(char *input, t_env **env)
{
    t_token *token_list = NULL;
    char *cur = input;
    char buffer[1024];
    int buf_idx = 0;
    t_content content = {&cur, buffer, &buf_idx, &token_list, *env};
    while (*cur)
    {
        if (*cur == ' ')
            handle_space(&cur, buffer, &buf_idx, &token_list);
        else if (*cur || *cur == '|' || *cur == '>' || *cur == '<' || *cur == '$' || *cur == '"' || *cur == '\'')
        {
            if(tokenize_helper(&content) == 1)
            {
                ft_tokens_free(token_list);
                return NULL;
            }
        }
    }
    if (buf_idx > 0)
    {
        buffer[buf_idx] = '\0';
        add_token(&token_list, create_token(buffer, WORD));
    }
    return token_list;
}
