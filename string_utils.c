/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"

char	*str_join(char *s1, char *s2)
{
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s = (char *)malloc(strlen(s1) + strlen(s2) + 1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	strcat(s, s1);
	strcat(s, s2);
	free(s1);
	free(s2);
	return (s);
}

char	*get_var_name(char *str)
{
	int	i;

	if (isdigit(str[0]) || str[0] == '$')
		return (strndup(str, 1));
	if (str[0] != '_' && !isalpha(str[0]))
		return (NULL);
	i = 1;
	while (str[i] && (str[i] == '_' || isalnum(str[i])))
		i++;
	return (strndup(str, i));
}

char	*get_value(char *key)
{
	if (key == NULL || *key == '\0')
		return (strdup("$"));
	else if (*key == '0')
		return (strdup("TODO: last exit status"));
	else if (*key == '$')
		return (strdup("TODO: pid"));
	else if (getenv(key) != NULL)
		return (strdup(getenv(key)));
	else
		return (strdup(""));
}

char	*replace_variables(char *str)
{
	char	*s;
	char	*p;
	char	*r;
	char	*key;

	s = strdup("");
	r = strchr(str, '$');
	p = str;
	while (r != NULL)
	{
		s = str_join(s, strndup(p, r - p));
		key = get_var_name(r + 1);
		s = str_join(s, get_value(key));
		if (key)
			p = r + strlen(key) + 1;
		else
			p = r + 1;
		free(key);
		r = strchr(p, '$');
	}
	s = str_join(s, strdup(p));
	free(str);
	return (s);
}
