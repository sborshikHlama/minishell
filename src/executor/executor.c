/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/24 20:54:00 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_builtin(t_ast_node *node, t_shell_state *shell_state)
{
	if (ft_strcmp(node->args[0], "pwd") == 0)
		*(shell_state->last_exit_code) = builtin_pwd();
	else if (ft_strcmp(node->args[0], "cd") == 0)
		*(shell_state->last_exit_code) = builtin_cd(node);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		*(shell_state->last_exit_code) = builtin_echo(node);
	else if (ft_strcmp(node->args[0], "env") == 0)
		*(shell_state->last_exit_code) = builtin_env(*(shell_state->envp));
	else if (ft_strcmp(node->args[0], "unset") == 0)
		*(shell_state->last_exit_code) = builtin_unset(node,
				shell_state->envp);
	else if (ft_strcmp(node->args[0], "export") == 0)
		*(shell_state->last_exit_code) = builtin_export(node,
				shell_state->envp);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		builtin_exit(node, shell_state);
}

// executes non builtin commands in a child process
void	exec_bin(t_ast_node *node, t_shell_state *shell_state)
{
	char	**all_paths;
	char	*exec_path;
	char	*env;

	env = ft_getenv("PATH", *(shell_state->envp));
	if (!env)
	{
		write(STDERR_FILENO, node->args[0], ft_strlen(node->args[0]));
		write(STDOUT_FILENO, ": command not found\n", 20);
		return ;	
	}
	all_paths = ft_split(env, ':');
	exec_path = get_exec_path(node, all_paths);
	if (all_paths)
		free_all_paths(all_paths);
	if (exec_path == NULL)
	{
		write(STDERR_FILENO, node->args[0], ft_strlen(node->args[0]));
		write(STDOUT_FILENO, ": command not found\n", 20);
		*(shell_state->last_exit_code) = 127;
		return ;
	}
	spawn_binary(exec_path, node, shell_state);
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

void	exec_redir(t_ast_node *node, t_shell_state *shell_state)
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
	exec_tree(cmd_node, shell_state);
	restore_fds(&saved_stdin, &saved_stdout);
}

// left-to-right iterarive tree traversal
// Start from the root (outermost pipe).
// Go left until reaching the first command (leftmost leaf).
// Execute each command, passing output to the next using pipes.
// Continue right until reaching the last command.

void	exec_tree(t_ast_node *node, t_shell_state *shell_state)
{
	if (!node)
		return ;
	if (node->type == NODE_REDIR)
		exec_redir(node, shell_state);
	if (node->type == NODE_PIPE)
		exec_pipe(node, shell_state);
	else if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			exec_builtin(node, shell_state);
		else
			exec_bin(node, shell_state);
	}
}
