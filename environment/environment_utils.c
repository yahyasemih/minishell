/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_utils.h"

char	**get_full_env(void)
{
	char	**env;
	t_env	*env_it;
	size_t	i;

	env = (char **)malloc(
			(get_env_size(g_minishell_ctx.env_list) + 1) * (sizeof(char **)));
	if (env == NULL)
		return (NULL);
	i = 0;
	env_it = g_minishell_ctx.env_list;
	while (env_it != NULL)
	{
		env[i] = env_it->entry;
		env_it = env_it->next;
		++i;
	}
	env[i] = NULL;
	return (env);
}

t_env	*generate_env(char **env)
{
	t_env	*env_list;
	t_env	*env_it;
	t_env	*head;
	int		i;

	env_list = NULL;
	head = NULL;
	i = 0;
	while (env[i])
	{
		env_it = (t_env *)malloc(sizeof(t_env));
		if (env_it == NULL)
			return (NULL);
		env_it->entry = str_dup(env[i]);
		env_it->next = env_list;
		env_list = env_it;
		head = env_list;
		++i;
	}
	return (head);
}

size_t	get_env_size(t_env *env)
{
	size_t	i;

	i = 0;
	while (env != NULL)
	{
		++i;
		env = env->next;
	}
	return (i);
}

void	add_new_env_entry(t_env **env_list, char *entry)
{
	t_env	*env_entry;

	if (env_list == NULL)
		return ;
	env_entry = (t_env *)malloc(sizeof(t_env));
	if (env_entry == NULL)
		return ;
	env_entry->entry = entry;
	env_entry->next = *env_list;
	*env_list = env_entry;
}

void	clear_env_list(void)
{
	t_env	*env_it;
	t_env	*next;

	env_it = g_minishell_ctx.env_list;
	while (env_it != NULL)
	{
		next = env_it->next;
		free(env_it->entry);
		free(env_it);
		env_it = next;
	}
	g_minishell_ctx.env_list = NULL;
}
