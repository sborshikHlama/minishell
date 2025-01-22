/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:48:42 by aevstign          #+#    #+#             */
/*   Updated: 2025/01/10 14:48:56 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(const char *name, char **env)
{
	int i;
	int name_len;

	if (!name || !env)
		return (NULL);
	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(name, env[i], name_len) == 0 && env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL); 
}

// void	env_expander(const char	*arg)
// {
// 	int	i;

// 	i = 0;
// 	if (arg[0] == '$')
// 	{

// 	}
// 	while (arg[i])
// 	{

// 	}

// }
