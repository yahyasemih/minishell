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
#include "environment_utils.h"

static void	handle_pipe(t_command **commands, t_command **command)
{
	t_command	*previous;
	int			pipe_fd[2];

	previous = *command;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (previous->output.type == STDOUT)
	{
		previous->output.value = str_dup("pipe");
		previous->output.type = IO_PIPE;
	}
	add_command(commands, previous);
	*command = new_command();
	if (*command == NULL)
		return ;
	(*command)->input.type = IO_PIPE;
	if (pipe(pipe_fd) < 0)
		printf("minishell: pipe error: %s\n", strerror(errno));
	if (previous->output.type == IO_PIPE)
		previous->output.fd = pipe_fd[1];
	else
		close(pipe_fd[1]);
	(*command)->input.fd = pipe_fd[0];
	(*command)->input.value = str_dup("pipe");
}

static void	process_tokens(t_token *token, t_command **commands)
{
	t_command	*command;

	command = new_command();
	if (command == NULL)
		return ;
	while (token && token->type != NEW_LINE && token->type != INVALID)
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
		g_minishell_ctx.should_execute = 0;
	commands = NULL;
	process_tokens(tokens, &commands);
	free_tokens(tokens);
	return (commands);
}

static void	init_minishell(char **env)
{
	char	*p;
	int		sh_lvl;

	g_minishell_ctx.env_list = generate_env(env);
	if (getenv("PWD") == NULL)
	{
		p = getcwd(NULL, 0);
		set_env("PWD", p);
		free(p);
	}
	sh_lvl = str_to_int(getenv("SHLVL"));
	if (sh_lvl < 0 || sh_lvl > 999)
		sh_lvl = 0;
	if (sh_lvl == 999)
		p = str_dup("");
	else
		p = int_to_str(sh_lvl + 1);
	set_env("SHLVL", p);
	free(p);
	g_minishell_ctx.exit_status = 0;
	g_minishell_ctx.is_executing = 0;
	g_minishell_ctx.is_cancelled = 0;
	g_minishell_ctx.should_execute = 1;
	install_signal_handlers();
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_command	*commands;

	if (argc != 1)
		exit(printf("Usage: %s with no argument\n", argv[0]));
	init_minishell(env);
	while (1)
	{
		line = readline("minish-1.0$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		commands = get_commands(line);
		if (g_minishell_ctx.should_execute)
			execute_commands(commands);
		else
			g_minishell_ctx.exit_status = 258;
		free_commands(commands);
		free(line);
		g_minishell_ctx.should_execute = 1;
		g_minishell_ctx.is_cancelled = 0;
	}
	clear_env_list();
	system("leaks minishell");
	return (g_minishell_ctx.exit_status);
}
