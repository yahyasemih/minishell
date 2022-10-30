/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum io_source_type {
	IO_PIPE,
	IO_HEREDOC,
	IN_REDIRECTION,
	OUT_REDIRECTION,
	OUT_APPEND,
	STDIN,
	STDOUT
}	t_io_source_type;

typedef struct io_source_s {
	char				*value;
	int					fd;
	t_io_source_type	type;
}	t_io_source;

typedef struct command_s {
	char				*cmd;
	char				**args;
	size_t				nb_args;
	t_io_source			input;
	t_io_source			output;
	struct command_s	*next;
}	t_command;

void		add_command(t_command **commands, t_command *command);
t_command	*new_command(void);
void		append_arg(t_command *command, char *arg);
void		free_commands(t_command *commands);

#endif //COMMANDS_H
