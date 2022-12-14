/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:13 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:15 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include "parsing.h"
# include "tokens.h"
# include "utilities.h"
# include "env_variables_utils.h"

int	handle_input_redirection(t_token **tokens, const char *str, size_t index);
int	handle_output_redirection(t_token **tokens, const char *str, size_t index);
int	handle_quoted_string(t_token **tokens, const char *str, size_t index,
		char q);
int	handle_simple_string(t_token **tokens, const char *str, size_t index);
int	handle_separator(t_token **tokens, const char *str, size_t index);

#endif //PARSING_UTILS_H
