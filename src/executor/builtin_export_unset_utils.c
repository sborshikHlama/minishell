/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:01:02 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/05 00:55:18 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	isname(char *name)
{
	int	i;

	if (ft_isalpha(name[0]) == 0 && name[0] != '_')
		return (FALSE);
	i = 0;
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_bool	check_envp(char *name, t_envp envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
			return (TRUE);
		++i;
	}
	return (FALSE);
}

t_status	print_envp(t_envp envp)
{
	int		i;
	char	*eq_pos;

	i = 0;
	while (envp[i] != NULL)
	{
		eq_pos = ft_strchr(envp[i], '=');
		write(STDOUT_FILENO, "declare -x ", 12);
		write(STDOUT_FILENO, envp[i], eq_pos + 1 - envp[i]);
		write(STDOUT_FILENO, "\"", 2);
		write(STDOUT_FILENO, eq_pos + 1, ft_strlen(eq_pos + 1));
		write(STDOUT_FILENO, "\"\n", 3);
		++i;
	}
	return (SUCCESS);
}
