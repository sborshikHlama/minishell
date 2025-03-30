/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:25:15 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/05 00:21:26 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	envp_add_new(char *new_var, t_envp *envp)
{
	t_envp	new_envp;
	int		i;

	new_envp = ft_calloc(envp_size(*envp) + 2, sizeof(char *));
	if (new_envp == NULL)
		return (FAILURE);
	i = 0;
	while ((*envp)[i] != NULL)
	{
		new_envp[i] = (*envp)[i];
		++i;
	}
	new_envp[i] = ft_strdup(new_var);
	if (new_envp[i] == NULL)
	{
		free(new_envp);
		return (FAILURE);
	}
	free(*envp);
	*envp = new_envp;
	return (SUCCESS);
}

static void	export_novalue(char *name, t_envp *envp, t_status *return_status)
{
	if (isname(name) == FALSE)
	{
		if (*return_status != FAILURE)
			error_export_name(name);
		*return_status = FAILURE;
		return ;
	}
	if (check_envp(name, *envp) == FALSE)
		if (envp_add_new(name, envp) == FAILURE)
			*return_status = FAILURE;
}

t_status	envp_replace_value(char *new_var, char *name, t_envp *envp)
{
	int		i;
	t_bool	offset;

	i = 0;
	offset = FALSE;
	new_var = ft_strdup(new_var);
	if (new_var == NULL)
		return (FAILURE);
	while ((*envp)[i] != NULL)
	{
		if (ft_strncmp(name, (*envp)[i], ft_strlen(name)) == 0
			&& ((*envp)[i][ft_strlen(name)] == '='
			|| (*envp)[i][ft_strlen(name)] == '\0'))
		{
			free((*envp)[i]);
			offset = TRUE;
		}
		else if (offset == TRUE)
			(*envp)[i - 1] = (*envp)[i];
		++i;
	}
	(*envp)[i - 1] = new_var;
	return (SUCCESS);
}

static void	export_value(char *new_var, char *eq_pos, t_envp *envp,
		t_status *return_status)
{
	char	*name;

	name = ft_strndup(new_var, eq_pos - new_var);
	if (name == NULL)
	{
		*return_status = FAILURE;
		return ;
	}
	if (isname(name) == FALSE)
	{
		if (*return_status != FAILURE)
			error_export_name(name);
		*return_status = FAILURE;
		free(name);
		return ;
	}
	if (check_envp(name, *envp) == FALSE)
	{
		if (envp_add_new(new_var, envp) == FAILURE)
			*return_status = FAILURE;
	}
	else if (envp_replace_value(new_var, name, envp) == FAILURE)
		*return_status = FAILURE;
	free(name);
}

/*
	export [name[=value]]

Add each name to be passed to child processes in the environment. If no
names are supplied a list of names of all exported variables is displayed.
If a variable name is followed by =value, the value of the variable is set
to value.

Errors:
The return status is zero unless one of the names is not a valid minishell
variable name, or there is malloc error.
*/
t_status	builtin_export(t_ast_node *node, t_envp *envp)
{
	int			i;
	char		*eq_pos;
	t_status	return_status;

	if (node->argc == 1)
		return (print_envp(*envp));
	i = 1;
	return_status = SUCCESS;
	while (i < node->argc)
	{
		eq_pos = strchr(node->args[i], '=');
		if (eq_pos == NULL)
			export_novalue(node->args[i], envp, &return_status);
		else
			export_value(node->args[i], eq_pos, envp, &return_status);
		i++;
	}
	return (return_status);
}
