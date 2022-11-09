/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_split.h"

static size_t	number_of_words(const char *str, const char *sep)
{
	size_t	i;
	size_t	count;

	if (str == NULL)
		return (0);
	if (sep == NULL)
		return (1);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str_chr(sep, str[i]) != NULL && str[i] != '\0')
			++i;
		if (str[i] == '\0')
			break ;
		++count;
		while (str_chr(sep, str[i]) == NULL && str[i] != '\0')
			++i;
	}
	return (count);
}

static char	*str_chr_any_of(const char *str, const char *set)
{
	size_t	i;
	char	*current;

	if (set == NULL || str == NULL)
		return (NULL);
	i = 0;
	while (set[i])
	{
		current = str_chr(str, set[i]);
		if (current != NULL)
			return (current);
		++i;
	}
	return (NULL);
}

static char	*extract_current_word(const char *str_it, const char *sep)
{
	char	*next_separator;

	next_separator = str_chr_any_of(str_it, sep);
	if (next_separator == NULL)
		return (str_dup(str_it));
	else
		return (str_n_dup(str_it, next_separator - str_it));
}

static void	free_words(char **words, size_t size)
{
	size_t	i;

	if (words == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free(words[i]);
		++i;
	}
	free(words);
}

char	**str_split(const char *str, const char *sep)
{
	size_t	i;
	char	**words;

	if (str == NULL)
		return (NULL);
	words = (char **) malloc((number_of_words(str, sep) + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	i = 0;
	while (str && *str)
	{
		while (str_chr(sep, *str) != NULL && *str != '\0')
			++str;
		if (*str == '\0')
			break ;
		words[i] = extract_current_word(str, sep);
		if (words[i] == NULL)
		{
			free_words(words, i);
			return (NULL);
		}
		str += str_len(words[i++]);
	}
	words[i] = NULL;
	return (words);
}
