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

#include "builtins_utils.h"
#include "execution_utils.h"
#include "execution.h"
#include "environment_utils.h"

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

static void	execute_command(t_command *command, t_command *commands)
{
	char	*path;
	int		pid;

	if (is_builtin(command->cmd) && nb_commands(commands) == 1)
	{
		g_minishell_ctx.exit_status = execute_builtin(command, commands);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(command->cmd))
			exit(execute_builtin(command, commands));
		dup2(command->input.fd, 0);
		dup2(command->output.fd, 1);
		close_fds(commands);
		path = find_command_ful_path(command);
		check_path(path, command->cmd);
		execve(path, command->args, get_full_env());
		free(path);
		dup2(2, 1);
		printf("minishell: %s: %s\n", command->cmd, strerror(errno));
		exit(126);
	}
	g_minishell_ctx.last_pid = pid;
}

static void	get_exit_status(void)
{
	waitpid(g_minishell_ctx.last_pid, &g_minishell_ctx.exit_status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(g_minishell_ctx.exit_status))
		g_minishell_ctx.exit_status = WEXITSTATUS(g_minishell_ctx.exit_status);
	else if (WIFSIGNALED(g_minishell_ctx.exit_status))
	{
		printf("%s", signal_name(g_minishell_ctx.exit_status));
		g_minishell_ctx.exit_status += 128;
	}
}

void	execute_commands(t_command *commands)
{
	t_command	*command;
	int			nb_non_empty_cmds;

	nb_non_empty_cmds = 0;
	if (g_minishell_ctx.is_cancelled || commands == NULL)
		return ;
	g_minishell_ctx.exit_status = 0;
	g_minishell_ctx.is_executing = 1;
	command = commands;
	while (command != NULL)
	{
		if (command->cmd != NULL
			&& (!is_builtin(command->cmd) || nb_commands(commands) != 1))
			nb_non_empty_cmds++;
		if (command->input.fd == -1 || command->output.fd == -1)
			g_minishell_ctx.exit_status = 1;
		if (command->cmd != NULL && command->input.fd != -1
			&& command->output.fd != -1)
			execute_command(command, commands);
		command = command->next;
	}
	close_fds(commands);
	if (nb_non_empty_cmds != 0)
		get_exit_status();
	g_minishell_ctx.is_executing = 0;
}
