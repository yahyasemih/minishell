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
#include "builtins_utils.h"

static void	close_fds(t_command *commands)
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

// TODO: find command in PATH or return NULL
// TODO: remove `str_join(strdup("/bin/"), strdup(command->cmd))`
static char	*find_command_ful_path(t_command *command)
{
	return (command->cmd);
	return (str_join(strdup("/bin/"), strdup(command->cmd)));
}

static void	execute_command(t_command *command, t_command *commands)
{
	char	*path;

	if (fork() == 0)
	{
		dup2(command->input.fd, 0);
		dup2(command->output.fd, 1);
		close_fds(commands);
		if (is_builtin(command))
			exit(execute_builtin(command));
		path = find_command_ful_path(command);
		if (path == NULL)
		{
			printf("minishell: %s: command not found\n", command->cmd);
			exit(127);
		}
		execve(path, command->args, NULL);
		perror("execve failed");
		exit(1);
	}
}

void	execute_commands(t_command *commands)
{
	t_command	*command;

	g_minishell_ctx.exit_status = 0;
	g_minishell_ctx.is_executing = 1;
	command = commands;
	while (command != NULL)
	{
		if (command->cmd != NULL && command->input.fd != -1
			&& command->output.fd != -1)
			execute_command(command, commands);
		command = command->next;
	}
	close_fds(commands);
	while (wait(&g_minishell_ctx.exit_status) > 0)
		;
	if (WIFEXITED(g_minishell_ctx.exit_status))
		g_minishell_ctx.exit_status = WEXITSTATUS(g_minishell_ctx.exit_status);
	else
	{
		printf("%s", signal_name(g_minishell_ctx.exit_status));
		g_minishell_ctx.exit_status += 128;
	}
	g_minishell_ctx.is_executing = 0;
}
