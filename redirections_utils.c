/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections_utils.h"

static void	process_heredoc(char *delimiter, int write_fd, int should_expand)
{
	char	*line;

	line = readline("> ");
	while (line != NULL && strcmp(line, delimiter) != 0)
	{
		if (should_expand)
			line = replace_variables(line);
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
}

static void	handle_heredoc(t_command *command, t_token *token)
{
	int	pipe_fd[2];

	if ((command->input.fd < 0 && command->input.value != NULL)
		|| (command->output.fd < 0 && command->output.value != NULL))
		return ;
	if (command->input.value != NULL)
	{
		free(command->input.value);
		close(command->input.fd);
	}
	if (pipe(pipe_fd) < 0)
		command->input.fd = -1;
	else
		command->input.fd = pipe_fd[0];
	command->input.type = IO_HEREDOC;
	command->input.value = strdup(token->next->value);
	if (command->input.fd < 0)
		printf("minishell: heredoc: %s\n", strerror(errno));
	else
	{
		process_heredoc(command->input.value, pipe_fd[1], !token->next->quoted);
		close(pipe_fd[1]);
	}
}

static void	handle_input_redirections(t_command *command, t_token *token)
{
	if ((command->input.fd < 0 && command->input.value != NULL)
		|| (command->output.fd < 0 && command->output.value != NULL))
		return ;
	if (command->input.value != NULL)
	{
		free(command->input.value);
		close(command->input.fd);
	}
	command->input.type = IN_REDIRECTION;
	command->input.value = strdup(token->next->value);
	command->input.fd = open(command->input.value, O_RDONLY);
	if (command->input.fd < 0)
		printf("minishell: %s: %s\n", command->input.value, strerror(errno));
}

static void	handle_output_redirections(t_command *command, t_token *token)
{
	if ((command->input.fd < 0 && command->input.value != NULL)
		|| (command->output.fd < 0 && command->output.value != NULL))
		return ;
	if (command->output.value != NULL)
	{
		free(command->output.value);
		close(command->output.fd);
	}
	if (token->type == OUTPUT_REDIRECTION)
	{
		command->output.type = OUT_REDIRECTION;
		command->output.value = strdup(token->next->value);
		command->output.fd = open(
				command->output.value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (token->type == OUTPUT_APPEND)
	{
		command->output.type = OUT_APPEND;
		command->output.value = strdup(token->next->value);
		command->output.fd = open(
				command->output.value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (command->output.fd < 0)
		printf("minishell: %s: %s\n", command->output.value, strerror(errno));
}

void	handle_redirections(t_command *command, t_token *token)
{
	if (token->next != NULL && token->next->type != STRING)
		return ;
	if (token->type == HEREDOC)
		handle_heredoc(command, token);
	else if (token->type == INPUT_REDIRECTION)
		handle_input_redirections(command, token);
	else
		handle_output_redirections(command, token);
}
