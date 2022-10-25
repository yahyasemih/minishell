/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:06:51 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:06:54 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "tokens.h"
# include "parsing_utils.h"
# include <stdio.h>

t_token	*parse_command(const char *str);
int		check_syntax(t_token *tokens);
void	remove_separator(t_token **tokens);

#endif //PARSING_H
