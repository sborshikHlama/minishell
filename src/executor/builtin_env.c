/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:25:15 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/03 19:52:56 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	builtin_env(t_envp envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (SUCCESS);
}
