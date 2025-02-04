/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/04 15:22:14 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_ast_node *node, t_envp *envp)
{
	if (ft_strcmp(node->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(node->args[0], "cd") == 0)
		builtin_cd(node);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		builtin_echo(node);
	else if (ft_strcmp(node->args[0], "env") == 0)
		builtin_env(*envp);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		builtin_exit(node, *envp);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		builtin_unset(node, envp);
	else if (ft_strcmp(node->args[0], "export") == 0)
		builtin_export(node, envp);
	// else if (ft_strcmp(node->args[0], "grep") == 0)
	// 	builtin_grep();
	// else if (ft_strcmp(node->args[0], "wc") == 0)
	// 	builtin_wc();
}

void	exec_tree(t_ast_node *node, t_envp *envp)
{
	if (!node)
		return ;
	// if (node->type == NODE_PIPE)
	// 	exec_pipe(node);
	else if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			exec_builtin(node, envp);
		// else
		// 	exec_bin(node);
	}
}
