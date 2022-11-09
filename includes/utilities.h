/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
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

int		str_cmp(const char *s1, const char *s2);
char	*int_to_str(int pid);
int		str_to_int(const char *str);
int		is_redirection(t_token *token);

#endif //UTILITIES_H
