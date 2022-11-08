/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env_builtin(t_command *command)
{
	size_t	i;

	(void)command;
	i = 0;
	while (g_minishell_ctx.env[i])
	{
		write(1, g_minishell_ctx.env[i], str_len(g_minishell_ctx.env[i]));
		write(1, "\n", 1);
		++i;
	}
	return (0);
}
