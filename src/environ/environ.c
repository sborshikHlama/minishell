/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:43:15 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/28 18:08:09 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

t_status	setup_envp(t_envp *dest)
{
	int	i;

	*dest = ft_calloc(envp_size(environ) + 1, sizeof(char *));
	if (*dest == NULL)
		return (FAILURE);
	i = 0;
	while (environ[i] != NULL)
	{
		(*dest)[i] = ft_strdup(environ[i]);
		if ((*dest)[i++] == NULL)
		{
			free_envp(*dest);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
