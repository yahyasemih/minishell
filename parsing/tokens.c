/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:30 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:31 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "utilities.h"

t_token_type	get_token_type(const char *value)
{
	if (value == NULL)
		return (INVALID);
	if (str_cmp(value, "<") == 0)
		return (INPUT_REDIRECTION);
	if (str_cmp(value, ">") == 0)
		return (OUTPUT_REDIRECTION);
	if (str_cmp(value, "<<") == 0)
		return (HEREDOC);
	if (str_cmp(value, ">>") == 0)
		return (OUTPUT_APPEND);
	if (str_cmp(value, "<<") == 0)
		return (HEREDOC);
	if (str_cmp(value, "|") == 0)
		return (PIPE);
	if (str_cmp(value, " ") == 0)
		return (SEPARATOR);
	if (str_cmp(value, "newline") == 0)
		return (NEW_LINE);
	return (STRING);
}

void	add_token(t_token **tokens, char *value, int is_string)
{
	t_token	*token;
	t_token	*it;

	if (tokens == NULL)
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return ;
	token->next = NULL;
	if (is_string)
		token->type = STRING;
	else
		token->type = get_token_type(value);
	token->value = value;
	token->quoted = 0;
	if (*tokens == NULL)
		*tokens = token;
	else
	{
		it = *tokens;
		while (it->next)
			it = it->next;
		it->next = token;
	}
}

t_token	*last_token(t_token *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*it;

	while (tokens)
	{
		it = tokens->next;
		free_token(tokens);
		tokens = it;
	}
}
