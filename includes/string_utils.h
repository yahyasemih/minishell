/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "minishell.h"
# include "parsing_utils.h"

size_t	str_len(const char *str);
char	*str_n_dup(const char *str, size_t n);
char	*str_dup(const char *str);
char	*str_join(char *s1, char *s2);
char	*str_chr(const char *str, char c);

#endif //STRING_UTILS_H
