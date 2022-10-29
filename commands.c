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

	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->next = NULL;
	command->args = NULL;
	command->cmd = NULL;
	command->nb_args = 0;
	command->input.type = STDIN;
	command->input.fd = -1;
	command->input.value = NULL;
	command->output.type = STDOUT;
	command->output.fd = -1;
	command->output.value = NULL;
	return (command);
}

void	append_arg(t_command *command, char *arg)
{
	if (command->nb_args == 0)
		command->cmd = strdup(arg);
	command->nb_args++;
	if (command->args == NULL)
		command->args = malloc(sizeof(char *) * (command->nb_args + 1));
	else
		command->args = realloc(command->args,
				(command->nb_args + 1) * sizeof(char *));
	command->args[command->nb_args - 1] = strdup(arg);
	command->args[command->nb_args] = NULL;
}

void	free_commands(t_command *commands)
{
	t_command	*it;
	size_t		i;

	while (commands)
	{
		it = commands->next;
		free(commands->input.value);
		free(commands->output.value);
		i = 0;
		while (i < commands->nb_args)
			free(commands->args[i++]);
		free(commands->args);
		free(commands->cmd);
		free(commands);
		commands = it;
	}
}
