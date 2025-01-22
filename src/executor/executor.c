/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/01/12 18:07:20 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_ast_node *node)
{
	if (ft_strcmp(node->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(node->args[0], "cd") == 0)
		builtin_cd(node);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		builtin_echo(node);
	// else if (ft_strcmp(node->args[0], "env") == 0)
	// 	builtin_env();
	// else if (ft_strcmp(node->args[0], "exit") == 0)
	// 	builtin_exit();
	// else if (ft_strcmp(node->args[0], "unset") == 0)
	// 	builtin_unset();
	// else if (ft_strcmp(node->args[0], "export") == 0)
	// 	builtin_export();
	// else if (ft_strcmp(node->args[0], "grep") == 0)
	// 	builtin_grep();
	// else if (ft_strcmp(node->args[0], "wc") == 0)
	// 	builtin_wc();
}

void	exec_tree(t_ast_node *node)
{
	if (!node)
		return ;
	// if (node->type == NODE_PIPE)
	// 	exec_pipe(node);
	else if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			exec_builtin(node);
		// else
		// 	exec_bin(node);
	}
}
