/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:06:39 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:06:44 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_utils.h"

char	*get_cmd_from_path(t_command *command)
{
	char	*p;
	char	*path;
	char	*curr;

	path = get_env("PATH");
	if (path == NULL)
		return (str_dup(command->cmd));
	p = str_chr(path, ':');
	while (p != NULL)
	{
		curr = str_join(str_join(str_n_dup(path, p - path), str_dup("/")),
				str_dup(command->cmd));
		if (!access(curr, F_OK))
			return (curr);
		path = p + 1;
		p = str_chr(path, ':');
		free(curr);
	}
	curr = str_join(str_dup(path), str_dup(command->cmd));
	if (!access(curr, F_OK))
		return (curr);
	free(curr);
	return (NULL);
}

char	*find_command_ful_path(t_command *command)
{
	if (command->cmd == NULL || *(command->cmd) == '\0')
		return (NULL);
	if (command->cmd[0] == '/')
		return (str_dup(command->cmd));
	if (str_chr(command->cmd, '/') != NULL)
		return (str_join(str_join(getcwd(NULL, 0), str_dup("/")),
				str_dup(command->cmd)));
	return (get_cmd_from_path(command));
}

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
