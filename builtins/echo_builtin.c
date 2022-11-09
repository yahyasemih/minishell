/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_option(const char *arg)
{
	int	i;

	if (arg == NULL || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		++i;
	}
	return (1);
}

int	echo_builtin(t_command *command)
{
	int		need_newline;
	size_t	i;

	need_newline = 1;
	i = 1;
	while (i < command->nb_args && is_valid_option(command->args[i]))
		++i;
	if (i > 1)
		need_newline = 0;
	while (i < command->nb_args)
	{
		write(command->output.fd, command->args[i], str_len(command->args[i]));
		++i;
		if (i < command->nb_args)
			write(command->output.fd, " ", 1);
	}
	if (need_newline)
		write(command->output.fd, "\n", 1);
	return (0);
}
