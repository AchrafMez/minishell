/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:03:59 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/04 03:04:09 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		printf("dexlare -x %s=\"%s\"\n", cur->key, cur->value);
		cur = cur->next;
	}
}
