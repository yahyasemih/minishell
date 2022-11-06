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

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type %d value '%s' quoted %d\n", tokens->type, tokens->value,
			tokens->quoted);
		tokens = tokens->next;
	}
}

void	print_commands(t_command *commands)
{
	int	i;

	while (commands)
	{
		printf("cmd '%s', input : '%s' (%d), output : '%s' (%d),  args(%zu) : ",
			commands->cmd, commands->input.value, commands->input.fd,
			commands->output.value, commands->output.fd, commands->nb_args);
		i = 0;
		if (commands->args)
		{
			printf("[");
			while (commands->args[i])
			{
				printf("'%s', ", commands->args[i]);
				i++;
			}
			printf("NULL]");
		}
		printf("\n");
		commands = commands->next;
	}
}

int	is_redirection(t_token *token)
{
	return (token->type == HEREDOC || token->type == INPUT_REDIRECTION
		|| token->type == OUTPUT_APPEND || token->type == OUTPUT_REDIRECTION);
}
