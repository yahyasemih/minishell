/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include "commands.h"
# include "execution.h"
# include "parsing.h"
# include "redirections_utils.h"
# include "signals.h"
# include "tokens.h"
# include "utilities.h"

typedef struct minishell_context_s
{
	int		exit_status;
	int		is_executing;
	int		should_execute;
	int		is_cancelled;
	int		dup_stdin_fd;
	char	**env;
	int		last_pid;
}	t_minishell_context;

t_minishell_context	g_minishell_ctx;

#endif //MINISHELL_H
