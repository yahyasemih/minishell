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

static void	handle_input_redirections(t_command *command, t_token *token)
{
	if (command->input.fd < 0)
		return ;
	free(command->input.value);
	close(command->input.fd);
	if (token->type == HEREDOC)
	{
		command->input.type = IO_HEREDOC;
		command->input.value = strdup(token->next->value);
	}
	else if (token->type == INPUT_REDIRECTION)
	{
		command->input.type = IN_REDIRECTION;
		command->input.value = strdup(token->next->value);
		command->input.fd = open(command->input.value, O_RDONLY);
	}
	if (command->input.fd < 0)
		printf("minishell: %s: %s\n", command->input.value, strerror(errno));
}

static void	handle_output_redirections(t_command *command, t_token *token)
{
	if (command->output.fd < 0)
		return ;
	free(command->output.value);
	close(command->output.fd);
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
				command->input.value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (command->output.fd < 0)
		printf("minishell: %s: %s\n", command->output.value, strerror(errno));
}

void	handle_redirections(t_command *command, t_token *token)
{
	if (token->type == HEREDOC || token->type == INPUT_REDIRECTION)
		handle_input_redirections(command, token);
	else
		handle_output_redirections(command, token);
}
