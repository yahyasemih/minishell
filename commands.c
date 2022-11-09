/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "string_utils.h"

int	nb_commands(t_command *commands)
{
	int	i;

	i = 0;
	while (commands != NULL)
	{
		i++;
		commands = commands->next;
	}
	return (i);
}

void	add_command(t_command **commands, t_command *command)
{
	t_command	*it;

	if (commands == NULL)
		return ;
	if (*commands == NULL)
		*commands = command;
	else
	{
		it = *commands;
		while (it->next)
			it = it->next;
		it->next = command;
	}
}

t_command	*new_command(void)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->next = NULL;
	command->args = NULL;
	command->cmd = NULL;
	command->nb_args = 0;
	command->input.type = STDIN;
	command->input.fd = 0;
	command->input.value = NULL;
	command->output.type = STDOUT;
	command->output.fd = 1;
	command->output.value = NULL;
	return (command);
}

void	append_arg(t_command *command, char *arg)
{
	char	**args;
	size_t	i;

	if (arg == NULL)
		return ;
	if (command->nb_args++ == 0)
		command->cmd = str_dup(arg);
	args = (char **)malloc(sizeof(char *) * (command->nb_args + 1));
	if (args == NULL)
		return ;
	if (command->args == NULL)
		command->args = args;
	else
	{
		i = 0;
		while (i < command->nb_args)
		{
			args[i] = command->args[i];
			++i;
		}
		free(command->args);
		command->args = args;
	}
	command->args[command->nb_args - 1] = str_dup(arg);
	command->args[command->nb_args] = NULL;
}

void	free_commands(t_command *commands)
{
	t_command	*it;
	size_t		i;

	while (commands)
	{
		it = commands->next;
		if (commands->input.value != NULL)
		{
			free(commands->input.value);
			close(commands->input.fd);
		}
		if (commands->output.value != NULL)
		{
			free(commands->output.value);
			close(commands->output.fd);
		}
		i = 0;
		while (i < commands->nb_args)
			free(commands->args[i++]);
		free(commands->args);
		free(commands->cmd);
		free(commands);
		commands = it;
	}
}
