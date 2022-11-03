/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:06:39 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:06:44 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*parse_command(const char *str)
{
	size_t	i;
	t_token	*tokens;

	tokens = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			i += handle_input_redirection(&tokens, str, i);
		else if (str[i] == '>')
			i += handle_output_redirection(&tokens, str, i);
		else if (str[i] == '|')
		{
			add_token(&tokens, strdup("|"));
			i++;
		}
		else if (str[i] == '"' || str[i] == '\'')
			i += handle_quoted_string(&tokens, str, i + 1, str[i]) + 1;
		else if (str[i] == ' ')
			i += handle_separator(&tokens, str, i);
		else
			i += handle_simple_string(&tokens, str, i);
	}
	add_token(&tokens, strdup("newline"));
	return (tokens);
}

static int	check_pipe(t_token *token, t_token *next)
{
	if (token != NULL && token->type == PIPE)
	{
		if (next == NULL || next->type == NEW_LINE)
			return (printf("minishell: syntax error: unexpected end of file\n"));
		if (next->type == PIPE)
			return (printf(
					"minishell: syntax error near unexpected token `|'\n"));
	}
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	if (token != NULL && token->type == PIPE)
		return (printf("minishell: syntax error near unexpected token `|'\n"));
	while (token)
	{
		if (token->type == NEW_LINE)
			return (0);
		if (token->type == INVALID)
			return (printf("minishell: syntax error: unexpected end of file\n"));
		if (token->type != STRING && token->type != PIPE
			&& (token->next == NULL || token->next->type != STRING))
		{
			if (token->next == NULL || token->next->value == NULL)
				return (printf(
						"minishell: syntax error: unexpected end of file"));
			return (printf("minishell: syntax error near unexpected token `%s'"
					"\n", token->next->value));
		}
		if (check_pipe(token, token->next))
			return (1);
		token = token->next;
	}
	return (0);
}

t_token_type	get_last_non_separator_type(t_token *tokens)
{
	t_token_type	type;

	type = INVALID;
	while (tokens != NULL)
	{
		if (tokens->type != SEPARATOR)
			type = tokens->type;
		tokens = tokens->next;
	}
	return (type);
}

void	remove_separator(t_token **tokens)
{
	t_token	*token;
	t_token	*prev;

	token = *tokens;
	while (token)
	{
		if (token->type == SEPARATOR)
		{
			if (token == *tokens)
			{
				*tokens = token->next;
				free_token(token);
				token = *tokens;
			}
			else
			{
				prev->next = token->next;
				free_token(token);
				token = prev;
			}
		}
		prev = token;
		token = token->next;
	}
}
