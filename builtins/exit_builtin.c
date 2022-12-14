/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environment_utils.h"

static int	str_status_to_int(const char *str, int *has_error)
{
	long long	val;
	int			i;
	int			sign;

	*has_error = 0;
	i = 0;
	sign = 1;
	while (str_chr(" \t\r\n\v\f", str[i]) != NULL)
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	val = 0;
	while (str[i] >= '0' && str[i] <= '9' && val >= 0)
		val = val * 10 + str[i++] - '0';
	if (str[i] != '\0' || val < 0)
		*has_error = 1;
	if (*has_error)
		val = INT64_MAX + (sign == -1);
	else
		val = sign * val;
	return ((int)val);
}

static int	is_valid_arg(const char *arg)
{
	int	has_error;

	str_status_to_int(arg, &has_error);
	return (has_error == 0);
}

static int	has_valid_arguments(t_command *command)
{
	size_t	i;

	i = 1;
	while (i < command->nb_args)
	{
		if (!is_valid_arg(command->args[i]))
			return (0);
		++i;
	}
	return (1);
}

static int	get_exit_status(t_command *command)
{
	int	status;
	int	has_error;

	if (command->nb_args > 2 && has_valid_arguments(command))
		return (1);
	status = str_status_to_int(command->args[1], &has_error);
	return (status);
}

int	exit_builtin(t_command *command, t_command *commands)
{
	int	exit_status;

	if (command->nb_args == 1)
		exit_status = 0;
	else
		exit_status = get_exit_status(command);
	if (nb_commands(commands) == 1)
		write(command->output.fd, "exit\n", 5);
	if (command->nb_args > 2 && is_valid_arg(command->args[1]))
		write(2, "minishell: exit: too many arguments\n", 36);
	else if (command->nb_args >= 2 && !is_valid_arg(command->args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, command->args[1], str_len(command->args[1]));
		write(2, ": numeric argument required\n", 28);
		exit_status = 255;
	}
	if (command->nb_args <= 2 || !is_valid_arg(command->args[1]))
	{
		free_commands(commands);
		clear_env_list();
		exit(exit_status);
	}
	return (exit_status);
}
