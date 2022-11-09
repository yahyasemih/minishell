/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_UTILS_H
# define REDIRECTIONS_UTILS_H

# include <errno.h>
# include <readline/readline.h>
# include <sys/fcntl.h>
# include <stdio.h>
# include <unistd.h>

# include "tokens.h"
# include "commands.h"
# include "string_utils.h"

void	handle_redirections(t_command *command, t_token *token);

#endif //REDIRECTIONS_UTILS_H
