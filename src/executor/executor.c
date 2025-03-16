/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/16 14:40:50 by aevstign         ###   ########.fr       */
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
}

// executes non builtin commands in a child process
void	exec_bin(t_ast_node *node, t_envp *envp, int *exit_status)
{
	char	**all_paths;
	char	*exec_path;

	all_paths = ft_split(ft_getenv("PATH", *envp), ':');
	exec_path = get_exec_path(node, all_paths);
	if (exec_path == NULL)
	{
		write(STDERR_FILENO, node->args[0], ft_strlen(node->args[0]));
		write(STDOUT_FILENO, ": command not found\n", 20);
		exit_status = 127;
		if (all_paths != NULL)
			free(all_paths);
		return ;
	}
	free(all_paths);
	spawn_binary(exec_path, node, envp, exit_status);
	free(exec_path);
}

// Open the target file:
// O_CREAT | O_WRONLY | O_TRUNC for >.
// O_CREAT | O_WRONLY | O_APPEND for >>.
// Use dup2(new_fd, STDOUT_FILENO) to replace stdout.
// Execute the command (execve()).

int	handle_redir_chain(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->left && node->left->type == NODE_REDIR)
		if (handle_redir_chain(node->left) < 0)
			return (-1);
	return (handle_redirections(node));
}

void	exec_redir(t_ast_node *node, t_envp *envp, int *exit_status)
{
	int			saved_stdout;
	int			saved_stdin;
	t_ast_node	*cmd_node;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (handle_redir_chain(node) < 0)
	{
		restore_fds(&saved_stdin, &saved_stdout);
		return ;
	}
	cmd_node = node;
	while (cmd_node && cmd_node->type == NODE_REDIR)
		cmd_node = cmd_node->left;
	exec_tree(cmd_node, envp, exit_status);
	restore_fds(&saved_stdin, &saved_stdout);
}

// left-to-right iterarive tree traversal
// Start from the root (outermost pipe).
// Go left until reaching the first command (leftmost leaf).
// Execute each command, passing output to the next using pipes.
// Continue right until reaching the last command.

void	exec_tree(t_ast_node *node, t_envp *envp, int *exit_status)
{
	if (!node)
		return ;
	if (node->type == NODE_REDIR)
		exec_redir(node, envp, exit_status);
	if (node->type == NODE_PIPE)
		exec_pipe(node, envp, exit_status);
	else if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			exec_builtin(node, envp, exit_status);
		else
			exec_bin(node, envp, exit_status);
	}
}
