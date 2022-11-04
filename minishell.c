/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipe(t_command **commands, t_command **command)
{
	t_command	*previous;
	int			pipe_fd[2];

	previous = *command;
	if (previous->output.type == STDOUT)
	{
		previous->output.value = strdup("pipe");
		previous->output.type = IO_PIPE;
	}
	add_command(commands, previous);
	*command = new_command();
	(*command)->input.type = IO_PIPE;
	if (pipe(pipe_fd) < 0)
	{
		previous->output.fd = -1;
		(*command)->input.fd = -1;
		printf("minishell: pipe: %s\n", strerror(errno));
		return ;
	}
	if (previous->output.type == IO_PIPE)
		previous->output.fd = pipe_fd[1];
	else
		close(pipe_fd[1]);
	(*command)->input.fd = pipe_fd[0];
	(*command)->input.value = strdup("pipe");
}

static void	process_tokens(t_token *token, t_command **commands)
{
	t_command	*command;

	command = new_command();
	while (token && token->type != NEW_LINE)
	{
		if (token->type == PIPE)
			handle_pipe(commands, &command);
		else if (is_redirection(token))
		{
			handle_redirections(command, token);
			token = token->next;
		}
		else
			append_arg(command, token->value);
		token = token->next;
	}
	add_command(commands, command);
}

static t_command	*get_commands(const char *line)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = parse_command(line);
	remove_separator(&tokens);
	if (check_syntax(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	commands = NULL;
	process_tokens(tokens, &commands);
	free_tokens(tokens);
	return (commands);
}

static void	init_minishell_context(char **env)
{
	g_minishell_ctx.env = env;
	g_minishell_ctx.exit_status = 0;
	g_minishell_ctx.is_executing = 0;
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_command	*commands;

	if (argc != 1)
	{
		printf("Usage: %s with no argument\n", argv[0]);
		exit(1);
	}
	init_minishell_context(env);
	install_signal_handlers();
	while (1)
	{
		line = readline("minish-1.0$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		commands = get_commands(line);
		execute_commands(commands);
		free_commands(commands);
		free(line);
	}
	return (0);
}
