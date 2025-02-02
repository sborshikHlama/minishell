/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:25:15 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/01 22:40:17 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	isname(char *name)
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

static t_bool	check_envp(char *name, t_envp envp)
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

static t_status	copy_envp(t_envp new_envp, t_envp old_envp, int size,
		char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (ft_strncmp(name, old_envp[i], ft_strlen(name)) != 0
			|| old_envp[i][ft_strlen(name)] != '=')
		{
			new_envp[j] = ft_strdup(old_envp[i]);
			if (new_envp[j] == NULL)
			{
				free_envp(new_envp);
				return (FAILURE);
			}
			++j;
		}
		++i;
	}
	return (SUCCESS);
}

static t_status	remove_in_envp(t_envp *envp, char *name)
{
	t_envp	new_envp;
	int		size;

	size = envp_size(*envp);
	if (size == 0)
		return (SUCCESS);
	new_envp = (char **)malloc(sizeof(char *) * size);
	if (new_envp == NULL)
		return (FAILURE);
	ft_memset(new_envp, 0, sizeof(char *) * (size));
	if (copy_envp(new_envp, *envp, size, name) == FAILURE)
		return (FAILURE);
	free_envp(*envp);
	*envp = new_envp;
	return (SUCCESS);
}

/*
	unset [name]
Remove each variable name from envp. Return status is zero unless a name
is not valid or there is malloc error.
*/
t_status	builtin_unset(t_ast_node *node, t_envp *envp)
{
	int			i;
	t_status	return_status;

	if (node->argc == 1)
	{
		error_unset_args();
		return (FAILURE);
	}
	return_status = SUCCESS;
	i = 1;
	while (i < node->argc)
	{
		if (isname(node->args[i]) == FALSE)
		{
			if (return_status != FAILURE)
				error_unset_name(node->args[i]);
			return_status = FAILURE;
		}
		else if (check_envp(node->args[i], *envp) == TRUE)
			if (remove_in_envp(envp, node->args[i]) == FAILURE)
				return_status = FAILURE;
		++i;
	}
	return (return_status);
}
