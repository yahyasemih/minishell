/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:07:38 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 08:07:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_UTILS_H
# define ENVIRONMENT_UTILS_H

# include "minishell.h"

char	**get_full_env(void);
t_env	*generate_env(char **env);
size_t	get_env_size(t_env *env);
void	add_new_env_entry(t_env **env_list, char *entry);
void	clear_env_list(void);

#endif //ENVIRONMENT_UTILS_H
