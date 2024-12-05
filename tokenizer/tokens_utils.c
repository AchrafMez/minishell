/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:15:48 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/12 11:15:49 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

t_token	*ret_last_token(t_token **token_list)
{
	t_token	*cur;

	cur = *token_list;
	if (!cur)
		return (NULL);
	while (cur->next)
		cur = cur->next;
	return (cur);
}

void	add_token(t_token **token_list, t_token *new_token)
{
	t_token	*cur;

	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		cur = ret_last_token(token_list);
		cur->next = new_token;
	}
}

void	print_tokens(t_token *token_list)
{
	t_token	*cur;

	cur = token_list;
	printf("\n");
	while (cur)
	{
		printf("token: |%s| token_type: |%u|\n", cur->value, cur->type);
		cur = cur->next;
	}
}

void	ft_tokens_free(t_token *token_list)
{
	t_token	*cur;
	t_token	*next;

	cur = token_list;
	while (cur)
	{
		next = cur->next;
		free(cur->value);
		free(cur);
		cur = next;
	}
}
