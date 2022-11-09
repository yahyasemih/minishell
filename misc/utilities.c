/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:47 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:48 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

int	str_cmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL && s2 != NULL)
		return (-1);
	if (s1 != NULL && s2 == NULL)
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char	*int_to_str(int pid)
{
	char	buff[12];
	int		i;
	int		p;

	i = 0;
	if (pid < 0)
		buff[i++] = '-';
	p = 1;
	while (pid / (p * 10) != 0 && p * 10 > p)
		p *= 10;
	while (p != 0 && i < 11)
	{
		buff[i++] = (char)((((pid / p) + 10) % 10) + '0');
		p /= 10;
	}
	buff[i] = '\0';
	return (str_dup(buff));
}

int	str_to_int(const char *str)
{
	long long	val;
	int			i;
	int			sign;

	if (str == NULL)
		return (0);
	i = 0;
	sign = 1;
	while (str_chr(" \t\r\n\v\f", str[i]) != NULL)
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	val = 0;
	while (str[i] >= '0' && str[i] <= '9' && val >= 0)
		val = val * 10 + str[i++] - '0';
	if (str[i] != '\0' || val < 0)
		return ((int)(INT64_MAX + (sign == -1)));
	return ((int)val * sign);
}

int	is_redirection(t_token *token)
{
	return (token->type == HEREDOC || token->type == INPUT_REDIRECTION
		|| token->type == OUTPUT_APPEND || token->type == OUTPUT_REDIRECTION);
}
