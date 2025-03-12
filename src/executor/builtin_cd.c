/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:48:37 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/04 23:57:13 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	builtin_cd(t_ast_node *node)
{
	if (node->argc < 2)
	{
		perror("cd");
		return (FAILURE);
	}
	else if (node->argc > 2)
	{
		perror("cd");
		return (FAILURE);
	}
	else if (chdir(node->args[1]) != 0)
	{
		perror("cd");
		return (FAILURE);
	}
	return (SUCCESS);
}
