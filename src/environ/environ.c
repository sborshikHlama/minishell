/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:43:15 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/02 21:33:10 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_envp(t_envp *dest, t_envp orig)
{
	int	envp_count;

	envp_count = 0;
	while (orig[envp_count] != NULL)
		++envp_count;
	if (envp_count == 0)
	{
		*dest = NULL;
		return (0);
	}
	*dest = (char **)malloc(sizeof(char *) * (envp_count + 1));
	if (*dest == NULL)
		return (1);
	ft_memset(*dest, 0, sizeof(char *) * (envp_count + 1));
	envp_count = 0;
	while (orig[envp_count] != NULL)
	{
		(*dest)[envp_count] = ft_strdup(orig[envp_count]);
		if ((*dest)[envp_count++] == NULL)
		{
			free_envp(*dest);
			return (1);
		}
	}
	return (0);
}
