/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:09:38 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/25 15:44:21 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str, char *target)
{
	if(!str && !target)
		return 0;
	if(!str)
		return -1;
	if(!target)
		return 1;
	while (*str && (*str == *target))
	{
		str++;
		target++;
	}
	return (*str - *target);
}
