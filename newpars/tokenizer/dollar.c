/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:55:08 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/27 16:15:34 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_dollar_helper(t_content *content, char *expanded, int flag)
{
	int	i;

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
		while (expanded[i] != '\0')
			content->buffer[(*content->buf_idx)++] = expanded[i++];
		if (flag == 1)
			add_token(content->token_list, create_token(content->buffer, WORD));
	}
}

void	handle_dollar(t_content *content, int flag)
{
	char	key[1024];
	char	*expanded;
	int		key_idx;

	key_idx = 0;
	(*content->cur)++;
	if (*(*content->cur) == '?')
	{
		expanded = get_env_value(content->env, "?");
		(*content->cur)++;
		while (*expanded)
			content->buffer[(*content->buf_idx)++] = *expanded++;
		return ;
	}
	while (**content->cur && (ft_isalnum(**content->cur)
			||**content->cur == '_'))
		key[key_idx++] = *(*content->cur)++;
	key[key_idx] = '\0';
	expanded = get_env_value(content->env, key);
	handle_dollar_helper(content, expanded, flag);
}
