/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	close_pipes(t_command *commands)
{
	while (commands != NULL)
	{
		if (commands->input.fd != 0)
			close(commands->input.fd);
		if (commands->output.fd != 1)
			close(commands->output.fd);
		commands = commands->next;
	}
}

void	execute_commands(t_command *commands)
{
	int			status;
	t_command	*command;

	status = 0;
	command = commands;
	while (command != NULL)
	{
		if (command->cmd != NULL && command->input.fd != -1
			&& command->output.fd != -1)
		{
			if (fork() == 0)
			{
				dup2(command->input.fd, 0);
				dup2(command->output.fd, 1);
				close_pipes(commands);
				execve(command->cmd, command->args, NULL);
				perror("execve failed");
				exit(1);
			}
		}
		command = command->next;
	}
	close_pipes(commands);
	while (wait(&status) > 0)
		;
}
