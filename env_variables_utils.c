/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   "env_variables_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:13 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:15 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables_utils.h"

static int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static char	*get_var_name(char *str)
{
	int	i;

	if (is_digit(str[0]) || str[0] == '$' || str[0] == '?')
		return (str_n_dup(str, 1));
	if (str[0] != '_' && !is_alpha(str[0]))
		return (NULL);
	i = 1;
	while (str[i] && (str[i] == '_' || is_alpha(str[i]) || is_digit(str[i])))
		i++;
	return (str_n_dup(str, i));
}

static char	*get_value(char *key)
{
	if (key == NULL || *key == '\0')
		return (str_dup("$"));
	else if (*key == '0')
		return (str_dup("minish"));
	else if (*key == '?')
		return (int_to_str(g_minishell_ctx.exit_status));
	else if (*key == '$')
		return (int_to_str(getpid()));
	else if (getenv(key) != NULL)
		return (str_dup(getenv(key)));
	else
		return (str_dup(""));
}

char	*replace_variables(char *str)
{
	char	*s;
	char	*p;
	char	*r;
	char	*key;

	s = str_dup("");
	r = str_chr(str, '$');
	p = str;
	while (r != NULL)
	{
		s = str_join(s, str_n_dup(p, r - p));
		key = get_var_name(r + 1);
		s = str_join(s, get_value(key));
		if (key)
			p = r + str_len(key) + 1;
		else
			p = r + 1;
		free(key);
		r = str_chr(p, '$');
	}
	s = str_join(s, str_dup(p));
	free(str);
	return (s);
}
