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

# include "commands.h"
# include "tokens.h"
# include <stdio.h>
# include <stdlib.h>

char	*str_join(char *s1, char *s2);
char	*replace_variables(char *str);
void	print_tokens(t_token *tokens);
void	print_commands(t_command *commands);
int		is_redirection(t_token *token);

#endif //UTILITIES_H
