/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_utils.h"
#include "utilities.h"
#include "builtins.h"

int	is_builtin(const char *command)
{
	return (!str_cmp("cd", command)
		|| !str_cmp("pwd", command)
		|| !str_cmp("env", command)
		|| !str_cmp("echo", command)
		|| !str_cmp("exit", command)
		|| !str_cmp("unset", command)
		|| !str_cmp("export", command));
}

// TODO: add builtin logic here
int	execute_builtin(t_command *command, t_command *commands)
{
	if (str_cmp("cd", command->cmd) == 0)
		return (cd_builtin(command));
	if (str_cmp("pwd", command->cmd) == 0)
		return (pwd_builtin(command));
	if (str_cmp("echo", command->cmd) == 0)
		return (echo_builtin(command));
	if (str_cmp("exit", command->cmd) == 0)
		return (exit_builtin(command, commands));
	return (0);
}
