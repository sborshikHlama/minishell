/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/12 16:35:20 by aevstign         ###   ########.fr       */
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
}

// executes non builtin commands in a child process
void	exec_bin(t_ast_node *node, t_envp *envp)
{
	char	**all_paths;
	char	*exec_path;
	pid_t	pid;

	all_paths = ft_split(get_env("PATH", envp), ':');
	exec_path = get_exec_path(node, all_paths);
	if (exec_path == NULL)
		return ;
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		if (execve(exec_path, node->args, (char **)*envp) < 0)
		{
			perror(exec_path);
			exit(1);
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

// Open the target file:
// O_CREAT | O_WRONLY | O_TRUNC for >.
// O_CREAT | O_WRONLY | O_APPEND for >>.
// Use dup2(new_fd, STDOUT_FILENO) to replace stdout.
// Execute the command (execve()).

void	handle_redir_chain(t_ast_node *node)
{
	if (node->left && node->left->type == NODE_REDIR)
	{
		printf("%s\n", node->redir.outfile);
		handle_redir_chain(node->left);
	}
	if (handle_redirections(node) < 0)
	{
		printf("failed to handle redirections\n");
		return ;
	}
}

void	exec_redir(t_ast_node *node, t_envp *envp)
{
	int			saved_stdout;
	int			saved_stdin;
	t_ast_node	*cmd_node;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	handle_redir_chain(node);
	cmd_node = node;
	while (cmd_node && cmd_node->type == NODE_REDIR)
		cmd_node = cmd_node->left;
	exec_tree(cmd_node, envp);
	restore_fds(&saved_stdin, &saved_stdout);
}

// left-to-right iterarive tree traversal
// Start from the root (outermost pipe).
// Go left until reaching the first command (leftmost leaf).
// Execute each command, passing output to the next using pipes.
// Continue right until reaching the last command.

void	exec_tree(t_ast_node *node, t_envp *envp)
{
	if (!node)
		return ;
	if (node->type == NODE_REDIR)
		exec_redir(node, envp);
	if (node->type == NODE_PIPE)
		exec_pipe(node, envp);
	else if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			exec_builtin(node, envp);
		else
			exec_bin(node, envp);
	}
}
