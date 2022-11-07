/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	error_msg(const char *cmd, const char *error, int is_perror)
{
	write(2, "minishell: ", 11);
	write(2, cmd, str_len(cmd));
	write(2, ": ", 2);
	if (is_perror)
		perror(error);
	else
		write(2, error, str_len(error));
	return (1);
}

static char	*handle_special_paths(t_command *command)
{
	char	*path;

	if (command->nb_args <= 1)
		path = getenv("HOME");
	else if (str_cmp(command->args[1], "-") == 0)
		path = getenv("OLDPWD");
	else
		path = command->args[1];
	if (path == NULL)
	{
		if (command->nb_args <= 1)
			error_msg(command->cmd, "HOME not set\n", 0);
		else if (str_cmp(command->args[1], "-") == 0)
			error_msg(command->cmd, "OLDPWD not set\n", 0);
		return (NULL);
	}
	return (path);
}

int	cd_builtin(t_command *command)
{
	char	*path;
	char	*pwd;

	path = handle_special_paths(command);
	if (path == NULL)
		return (1);
	if (chdir(path) < 0)
		return (error_msg(command->cmd, path, 1));
	if (command->nb_args >= 2 && str_cmp(command->args[1], "-") == 0)
	{
		write(command->output.fd, getenv("OLDPWD"), str_len(getenv("OLDPWD")));
		write(command->output.fd, "\n", 1);
	}
	pwd = getenv("PWD");
	if (pwd != NULL)
		setenv("OLDPWD", getenv("PWD"), 1);
	pwd = getcwd(NULL, 0);
	setenv("PWD", pwd, 1);
	free(pwd);
	return (0);
}
