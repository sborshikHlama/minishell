/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:04:25 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/07 13:10:04 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	builtin_echo(t_ast_node *node)
{
	int	start;
	int	new_line;

	start = 1;
	new_line = 1;
	if (node->argc > 1 && ft_strcmp(node->args[1], "-n") == 0)
	{
		new_line = 0;
		++start;
	}
	while (start < node->argc)
	{
		write(STDOUT_FILENO, node->args[start], ft_strlen(node->args[start]));
		if (++start != node->argc)
			write(STDOUT_FILENO, " ", 1);
	}
	if (new_line == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
