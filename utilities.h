/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:54 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:56 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <stdio.h>
# include <stdlib.h>

# include "commands.h"
# include "string_utils.h"
# include "tokens.h"

char	*pid_to_str(pid_t pid);
void	print_tokens(t_token *tokens);
void	print_commands(t_command *commands);
int		is_redirection(t_token *token);

#endif //UTILITIES_H
