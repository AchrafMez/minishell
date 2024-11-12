/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:15:15 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/12 11:15:16 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_red_in(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
	if (*buf_idx > 0)
	{
		buffer[*buf_idx] = '\0';
		add_token(token_list, create_token(buffer, WORD));
		*buf_idx = 0;
	}
	if (*(*cur + 1) == '<')
	{
		add_token(token_list, create_token("<<", HERE_DOC));
		(*cur)++;
	}
	else
		add_token(token_list, create_token("<", RED_IN));
	(*cur)++;
	if (**cur == '<' || **cur == '>')
	{
		printf("syntax error near unexpected token '<' \n");
		return (1);
	}
	return (0);
}

int	handle_red_out(char **cur, char *buffer, int *buf_idx, t_token **token_list)
{
	if (*buf_idx > 0)
	{
		buffer[*buf_idx] = '\0';
		add_token(token_list, create_token(buffer, WORD));
		*buf_idx = 0;
	}
	if (*(*cur + 1) == '>')
	{
		add_token(token_list, create_token(">>", RED_APP));
		(*cur)++;
	}
	else
		add_token(token_list, create_token(">", RED_OUT));
	(*cur)++;
	if (**cur == '>' || **cur == '<')
	{
		printf("Syntax error near unexpected token '>' \n");
		return (1);
	}
	return (0);
}
