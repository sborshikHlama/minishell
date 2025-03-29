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

t_status	update_shlvl(t_envp *envp)
{
	char	*shlvl_val;
	char	*shlvl;

	shlvl_val = ft_getenv("SHLVL", *envp);
	if (shlvl_val != NULL)
	{
		shlvl_val = ft_itoa(ft_atoi(shlvl_val) + 1);
		if (shlvl_val == NULL)
			return (FAILURE);
		shlvl = ft_strjoin("SHLVL=", shlvl_val);
		free(shlvl_val);
		if (shlvl == NULL)
			return (FAILURE);
		if (envp_replace_value(shlvl, "SHLVL", envp) == FAILURE)
		{
			free(shlvl);
			return (FAILURE);
		}
		free(shlvl);
	}
	else if (envp_add_new("SHLVL=1", envp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

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
	if (update_shlvl(dest) == FAILURE)
	{
		free_envp(*dest);
		return (FAILURE);
	}
	return (SUCCESS);
}
