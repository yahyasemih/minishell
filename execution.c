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

static char	*get_cmd_from_path(t_command *command)
{
	char	*p;
	char	*path;
	char	*curr;

	path = getenv("PATH");
	if (path == NULL)
		return (command->cmd);
	p = strchr(path, ':');
	while (p != NULL)
	{
		curr = str_join(str_join(strndup(path, p - path), strdup("/")),
				strdup(command->cmd));
		if (!access(curr, F_OK))
			return (curr);
		path = p + 1;
		p = strchr(path, ':');
	}
	curr = str_join(strdup(path), strdup(command->cmd));
	if (!access(curr, F_OK))
		return (curr);
	return (NULL);
}

static char	*find_command_ful_path(t_command *command)
{
	if (command->cmd == NULL || command->cmd[0] == '/')
		return (command->cmd);
	if (strchr(command->cmd, '/') != NULL)
		return (str_join(str_join(getcwd(NULL, 0), strdup("/")),
				strdup(command->cmd)));
	return (get_cmd_from_path(command));
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
		printf("minishell: %s: %s\n", command->cmd, strerror(errno));
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
