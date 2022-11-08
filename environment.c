/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "environment_utils.h"
#include "minishell.h"

char	*get_env(const char *name)
{
	t_env	*env_it;
	char	*key;

	env_it = g_minishell_ctx.env_list;
	while (env_it != NULL)
	{
		key = str_n_dup(env_it->entry, str_len(name));
		if (key && !str_cmp(key, name) && str_chr(env_it->entry, '=') != NULL)
		{
			free(key);
			return (str_chr(env_it->entry, '=') + 1);
		}
		free(key);
		env_it = env_it->next;
	}
	return (NULL);
}

void	set_env(const char *name, const char *value)
{
	t_env	*env_it;
	char	*entry;
	char	*key;

	entry = str_join(str_dup(name), str_join(str_dup("="), str_dup(value)));
	env_it = g_minishell_ctx.env_list;
	while (env_it != NULL)
	{
		key = str_n_dup(env_it->entry, str_len(name));
		if (str_cmp(name, key) == 0)
		{
			free(env_it->entry);
			free(key);
			env_it->entry = entry;
			return ;
		}
		free(key);
		env_it = env_it->next;
	}
	add_new_env_entry(&g_minishell_ctx.env_list, entry);
}

static int	check_first_env_entry(const char *name)
{
	char	*key;
	t_env	*env_entry;

	key = str_n_dup(g_minishell_ctx.env_list->entry, str_len(name));
	if (str_cmp(key, name) == 0)
	{
		env_entry = g_minishell_ctx.env_list->next;
		free(g_minishell_ctx.env_list->entry);
		free(g_minishell_ctx.env_list);
		g_minishell_ctx.env_list = env_entry;
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

void	unset_env(const char *name)
{
	t_env	*env_it;
	t_env	*previous;
	char	*key;

	if (g_minishell_ctx.env_list == NULL)
		return ;
	if (check_first_env_entry(name))
		return ;
	previous = g_minishell_ctx.env_list;
	env_it = g_minishell_ctx.env_list->next;
	while (env_it != NULL)
	{
		key = str_n_dup(env_it->entry, str_len(name));
		if (str_cmp(key, name) == 0)
		{
			free(key);
			free(env_it->entry);
			previous->next = env_it->next;
			free(env_it);
			return ;
		}
		free(key);
		previous = env_it;
		env_it = env_it->next;
	}
}
