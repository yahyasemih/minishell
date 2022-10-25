/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stdlib.h>
# include <string.h>

// TODO: add more types
typedef enum token_type {
	STRING,
	INPUT_REDIRECTION,
	OUTPUT_REDIRECTION,
	OUTPUT_APPEND,
	HEREDOC,
	PIPE,
	SEPARATOR,
	NEW_LINE,
	INVALID
}	t_token_type;

typedef struct token_s {
	t_token_type	type;
	char			*value;
	struct token_s	*next;
}	t_token;

t_token_type	get_token_type(const char *value);
void			add_token(t_token **tokens, char *value);
t_token			*last_token(t_token *tokens);
void			free_token(t_token *token);
void			free_tokens(t_token *tokens);

#endif //TOKENS_H
