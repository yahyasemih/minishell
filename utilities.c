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

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type %d value '%s'\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

void	print_commands(t_command *commands)
{
	int	i;

	while (commands)
	{
		printf("cmd '%s' nb args '%zu'\n", commands->cmd, commands->nb_args);
		i = 0;
		if (commands->args)
		{
			printf("[");
			while (commands->args[i])
			{
				printf("'%s', ", commands->args[i]);
				i++;
			}
			printf("NULL]\n");
		}
		commands = commands->next;
	}
}

int	is_redirection(t_token *token)
{
	return (token->type == HEREDOC || token->type == INPUT_REDIRECTION
		|| token->type == OUTPUT_APPEND || token->type == OUTPUT_REDIRECTION);
}
