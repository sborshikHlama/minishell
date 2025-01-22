/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-22 12:04:25 by dnovak            #+#    #+#             */
/*   Updated: 2025-01-22 12:04:25 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void builtin_echo(t_ast_node *node)
{
    int start;
    int new_line;

    start = 1;
    new_line = 1;
    if (node->argc > 1 && ft_strcmp(node->args[1], "-n") == 0)
    {
        new_line = 0;
        ++start;
    }
    while (start < node->argc)
    {
        write(1, node->args[start], ft_strlen(node->args[start]));
        if (++start != node->argc)
            write(1, " ", 1);
    }
    if (new_line == 1)
        write(1, "\n", 1);

}





