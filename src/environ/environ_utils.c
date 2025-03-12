/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:48:40 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/10 18:33:02 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envp(t_envp envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		++i;
	}
	free(envp);
}

int	envp_size(t_envp envp)
{
	int	size;

	size = 0;
	while (envp[size] != NULL)
		++size;
	return (size);
}

char	*get_env(char *env_name, t_envp *envp)
{
	int		i;
	int		env_len;
	char	*path_line;

	i = 0;
	env_len = ft_strlen(env_name);
	path_line = NULL;
	while ((*envp)[i] != NULL)
	{
		if (ft_strncmp((*envp)[i], env_name, env_len) == 0)
		{
			path_line = (*envp)[i];
			break ;
		}
		i++;
	}
	i = 0;
	if (path_line != NULL)
		while (path_line[i] != '=')
			i++;
	return (path_line + i + 1);
}
