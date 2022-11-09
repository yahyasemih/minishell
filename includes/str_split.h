/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_SPLIT_H
# define STR_SPLIT_H

# include <stdlib.h>
# include "string_utils.h"

char	**str_split(const char *str, const char *sep);

#endif //STR_SPLIT_H
