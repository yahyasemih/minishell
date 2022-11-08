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
	t_env	*env_it;

	(void)command;
	env_it = g_minishell_ctx.env_list;
	while (env_it != NULL)
	{
		write(command->output.fd, env_it->entry,
			str_len(env_it->entry));
		write(command->output.fd, "\n", 1);
		env_it = env_it->next;
	}
	return (0);
}
