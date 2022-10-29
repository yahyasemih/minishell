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

void	process_tokens(t_token *token, t_command **commands)
{
	t_command	*command;

	command = new_command();
	while (token && token->type != NEW_LINE)
	{
		if (token->type == PIPE)
		{
			command->output.type = IO_PIPE;
			command->output.value = NULL;
			add_command(commands, command);
			command = new_command();
			command->input.type = IO_PIPE;
			command->input.value = NULL;
		}
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

t_command	*get_commands(const char *line)
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

int	main(void)
{
	char		*line;
	t_command	*commands;

	while (1)
	{
		line = readline("$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		commands = get_commands(line);
		print_commands(commands);
		free_commands(commands);
		free(line);
	}
	system("leaks minishell");
	return (0);
}
