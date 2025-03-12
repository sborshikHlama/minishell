/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:48:40 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/08 21:48:02 by dnovak           ###   ########.fr       */
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

char	*ft_getenv(const char *name, t_envp envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
			return (&(envp[i][ft_strlen(name) + 1]));
		++i;
	}
	return (NULL);
}
