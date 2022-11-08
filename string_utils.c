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

size_t	str_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*str_dup(const char *str)
{
	char	*s;
	int		i;

	s = (char *)malloc((str_len(str) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*str_n_dup(const char *str, size_t n)
{
	char	*s;
	size_t	i;
	size_t	len;

	len = str_len(str);
	if (n > len)
		n = len;
	s = (char *)malloc((n + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*str_join(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	s = (char *)malloc(str_len(s1) + str_len(s2) + 1);
	if (s == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		s[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		s[i + j] = s2[j];
	s[i + j] = '\0';
	free(s1);
	free(s2);
	return (s);
}

char	*str_chr(const char *str, char c)
{
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)(str + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(str + i));
	return (NULL);
}
