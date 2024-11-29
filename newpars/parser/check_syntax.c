/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:11:03 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/27 18:22:55 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax(t_token *token)
{
	t_token	*cur;

	cur = token;
	if(cur->type == PIPE)
    {
        printf("syntax error near unexpected token '|'\n");
        return 258;
    }
	while (cur)
	{
		if (cur->type == PIPE)
		{
			if (!cur->next || cur->next->type == PIPE)
			{
				printf("minishell$: syntax error near '|' \n");
				return (258);
			}
		}
		else if (cur->type == RED_IN || cur->type == RED_OUT
			|| cur->type == HERE_DOC || cur->type == RED_APP)
		{
			if (!cur->next || (cur->next->type != WORD
				&& cur->next->type != SPACES && cur->next->type != S_QUOTE
				&& cur->next->type != D_QUOTE))
			{
				printf("minishell$: syntax error near > < \n");
				return (258);
			}
		}
		cur = cur->next;
	}
	return (0);
}

int	check_unclosed_quotes(char *input)
{
	int s_quotes = 0;
	int d_quotes = 0;
	while (*input)
	{
		if (*input == '\'' && !d_quotes)
			s_quotes = !s_quotes;
		else if (*input == '"' && !s_quotes)
			d_quotes = !d_quotes;
		input++;
	}
	if (s_quotes)
	{
		printf("minishell$: singel quotes not closed\n");
		return (258);
	}
	if (d_quotes)
	{
		printf("minishell$: double quotes not closed\n");
		return (258);
	}
	return (0);
}
