/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:04 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:07 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

int	handle_input_redirection(t_token **tokens, const char *str, size_t index)
{
	if (str[index + 1] != '<')
	{
		add_token(tokens, str_dup("<"));
		return (1);
	}
	else
	{
		add_token(tokens, str_dup("<<"));
		return (2);
	}
}

int	handle_output_redirection(t_token **tokens, const char *str, size_t index)
{
	if (str[index + 1] == '>')
	{
		add_token(tokens, str_dup(">>"));
		return (2);
	}
	else
	{
		add_token(tokens, str_dup(">"));
		return (1);
	}
}

int	handle_quoted_string(t_token **tokens, const char *str, size_t index,
	char q)
{
	int		i;
	char	*val;
	t_token	*last;

	i = 0;
	while (str[index + i] && str[index + i] != q)
		++i;
	if (str[index + i] == q)
	{
		val = str_n_dup(str + index, i);
		if (q == '"' && str_chr(val, '$') != NULL)
			val = replace_variables(val);
		last = last_token(*tokens);
		if (last != NULL && last->type == STRING)
			last->value = str_join(last->value, val);
		else
			add_token(tokens, val);
		last = last_token(*tokens);
		last->quoted |= 1;
		if (last->quoted)
			last->type = STRING;
		return (i + 1);
	}
	add_token(tokens, NULL);
	return (i);
}

int	handle_simple_string(t_token **tokens, const char *str, size_t index)
{
	int		i;
	char	*val;
	t_token	*last;

	i = 0;
	while (str[index + i] != '\0' && str_chr(" \"'<>|", str[index + i]) == NULL)
		++i;
	val = str_n_dup(str + index, i);
	if (str_chr(val, '$') != NULL
		&& get_last_non_separator_type(*tokens) != HEREDOC)
		val = replace_variables(val);
	last = last_token(*tokens);
	if (last != NULL && last->type == STRING)
		last->value = str_join(last->value, val);
	else
		add_token(tokens, val);
	return (i);
}

int	handle_separator(t_token **tokens, const char *str, size_t index)
{
	int	i;

	i = 0;
	while (str[index + i] == ' ')
		++i;
	if (i > 0)
		add_token(tokens, str_dup(" "));
	return (i);
}
