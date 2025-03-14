/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/05 00:02:23 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_builtin(t_ast_node *node, t_envp *envp, int *exit_status)
{
	if (ft_strcmp(node->args[0], "pwd") == 0)
		*exit_status = builtin_pwd();
	else if (ft_strcmp(node->args[0], "cd") == 0)
		*exit_status = builtin_cd(node);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		*exit_status = builtin_echo(node);
	else if (ft_strcmp(node->args[0], "env") == 0)
		*exit_status = builtin_env(*envp);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		*exit_status = builtin_unset(node, envp);
	else if (ft_strcmp(node->args[0], "export") == 0)
		*exit_status = builtin_export(node, envp);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		builtin_exit(node, *envp, *exit_status);
	// else if (ft_strcmp(node->args[0], "grep") == 0)
	// 	builtin_grep();
	// else if (ft_strcmp(node->args[0], "wc") == 0)
	// 	builtin_wc();
}

void	exec_tree(t_ast_node *node, t_envp *envp, int *exit_status)
{
	if (!node)
		return ;
	// if (node->type == NODE_PIPE)
	// 	exec_pipe(node);
	else if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			exec_builtin(node, envp, exit_status);
		// else
		// 	exec_bin(node);
	}
}
