/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:06:39 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:06:44 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_UTILS_H
# define EXECUTION_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include "minishell.h"

void	check_path(const char *path, const char *src);
char	*find_command_ful_path(t_command *command);
char	*get_cmd_from_path(t_command *command);

#endif //EXECUTION_UTILS_H