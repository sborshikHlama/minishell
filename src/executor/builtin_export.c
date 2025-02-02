/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:25:15 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/01 21:50:29 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_export(t_ast_node *node, t_envp *envp)
{
	int	i;

	if (node->argc == 1)
	{
		builtin_env(*envp);
		return ;
	}
	i = 1;
	while (i < node->argc)
	{
		/*find first '=' char and save its position*/
		/*check left part (name) contains only alphanum and '_' and starts with letter or '_'*/
		/*CHECK if name is already in envp*/
		/*yes - change value*/
		/*no - change */
		/*save value*/
		i++;
	}
}
