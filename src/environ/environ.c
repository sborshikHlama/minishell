/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:43:15 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/20 10:41:34 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	setup_envp(t_envp *dest, t_envp orig)
{
	int	envp_count;

	envp_count = envp_size(orig);
	*dest = ft_calloc(envp_count + 1, sizeof(char *));
	if (*dest == NULL)
		return (FAILURE);
	envp_count = 0;
	while (orig[envp_count] != NULL)
	{
		(*dest)[envp_count] = ft_strdup(orig[envp_count]);
		if ((*dest)[envp_count++] == NULL)
		{
			free_envp(*dest);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
