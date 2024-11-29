/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:12:18 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/27 16:33:29 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void delete_space(t_token **token_list)
{
    t_token *cur;
    t_token *prev;

    cur = *token_list;
    prev = NULL;

    if (cur && (cur->type == SPACES || ft_strcmp(cur->value, " ") == 0))
    {
        *token_list = cur->next;
        free(cur->value);
        free(cur);
        return;
    }

    while (cur != NULL && (cur->type != SPACES && ft_strcmp(cur->value, " ") != 0))
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur != NULL)
    {
        prev->next = cur->next;
        free(cur->value);
        free(cur);
    }
}

void tokens_edit(t_token **token_list)
{
    t_token *cur;

    cur = *token_list;
    while (cur)
    {
        if (cur->type == SPACES || (cur->type == ENV && (cur->value == NULL || ft_strlen(cur->value) == 0)))
        {
            delete_space(token_list);
            cur = *token_list;
        }
        else
            cur = cur->next;
    }
}
