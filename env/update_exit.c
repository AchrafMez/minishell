/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 04:50:34 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/05 07:46:50 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_exit_value(t_env **env, int status)
{
	char	*value;

	value = ft_itoa(status);
	set_export_env(env, "?", value);
	free(value);
}
