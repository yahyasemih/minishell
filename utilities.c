/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:47 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:48 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

char	*pid_to_str(pid_t pid)
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
		buff[i++] = (((pid / p) + 10) % 10) + '0';
		p /= 10;
	}
	buff[i] = '\0';
	return (strdup(buff));
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
		printf("cmd '%s', input : '%s', output : '%s',  args(%zu) : ",
			commands->cmd, commands->input.value, commands->output.value,
			commands->nb_args);
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
