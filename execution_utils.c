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

	path = getenv("PATH");
	if (path == NULL)
		return (strdup(command->cmd));
	p = strchr(path, ':');
	while (p != NULL)
	{
		curr = str_join(str_join(strndup(path, p - path), strdup("/")),
				strdup(command->cmd));
		if (!access(curr, F_OK))
			return (curr);
		path = p + 1;
		p = strchr(path, ':');
		free(curr);
	}
	curr = str_join(strdup(path), strdup(command->cmd));
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
		return (strdup(command->cmd));
	if (strchr(command->cmd, '/') != NULL)
		return (str_join(str_join(getcwd(NULL, 0), strdup("/")),
				strdup(command->cmd)));
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
