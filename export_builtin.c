/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_key(const char *entry)
{
	char	*key;
	char	*p;

	p = str_chr(entry, '=');
	if (p == NULL)
		key = str_dup(entry);
	else
		key = str_n_dup(entry, p - entry);
	return (key);
}

static char	*get_value(const char *entry)
{
	char	*value;
	char	*p;

	p = str_chr(entry, '=');
	if (p == NULL)
		value = NULL;
	else
		value = str_dup(p + 1);
	return (value);
}

static int	is_valid_key(const char *key)
{
	size_t	i;

	if ((key[0] < 'a' || key[0] > 'z') && (key[0] < 'A' || key[0] > 'Z')
		&& key[0] != '_')
		return (0);
	i = 1;
	while (key[i] == '_' || (key[i] >= '0' && key[i] <= '9')
		|| (key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z'))
		++i;
	return (key[i] == '\0');
}

static int	error_msg(const char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, str_len(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	export_builtin(t_command *command)
{
	size_t	i;
	char	*key;
	char	*value;
	int		return_value;

	i = 1;
	return_value = 0;
	while (i < command->nb_args)
	{
		key = get_key(command->args[i]);
		if (!is_valid_key(key))
			return_value = error_msg(command->args[i]);
		else
		{
			value = get_value(command->args[i]);
			if (value != NULL)
			{
				set_env(key, value);
				free(value);
			}
		}
		free(key);
		++i;
	}
	return (return_value);
}
