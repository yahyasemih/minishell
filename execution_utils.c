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

#include "execution_utils.h"

static int	is_directory(const char *path)
{
	struct stat	stat_s;

	if (stat(path, &stat_s) < 0)
		return (0);
	if (S_ISDIR(stat_s.st_mode))
		return (1);
	return (0);
}

void	check_path(const char *path, const char *src)
{
	if (path == NULL)
	{
		dup2(2, 1);
		printf("minishell: %s: command not found\n", src);
		exit(127);
	}
	if (is_directory(path))
	{
		dup2(2, 1);
		printf("minishell: %s: is a directory\n", src);
		exit(126);
	}
}
