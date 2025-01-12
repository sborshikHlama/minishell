/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:48:37 by aevstign          #+#    #+#             */
/*   Updated: 2025/01/12 18:01:19 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_cd(t_ast_node *node)
{
	if (node->argc < 2)
	{
		write(1, "cd: missing argument\n", 21);
		return ;
	}
	else if (node->argc > 2)
	{
		write(1, "cd: too many arguments\n", 23);
		return ;
	}
	else if (chdir(node->args[1]) != 0)
	{
		write(1, "cd: error", 9);
		return ;
	}
}