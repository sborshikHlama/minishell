/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:48:40 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/01 21:00:11 by dnovak           ###   ########.fr       */
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
