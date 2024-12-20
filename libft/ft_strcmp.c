/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: captain <captain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:09:38 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/05 08:02:28 by captain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *str, char *target)
{
	if (!str && !target)
		return (0);
	if (!str)
		return (-1);
	if (!target)
		return (1);
	while (*str && (*str == *target))
	{
		str++;
		target++;
	}
	return (*str - *target);
}
