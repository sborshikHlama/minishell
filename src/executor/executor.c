/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/09 12:38:52 by aevstign         ###   ########.fr       */
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

// need to compare first 4 letters of each string in envp with string PATH
char	*get_env(char *env_name, t_envp *envp)
{
	int		i;
	int		env_len;
	char	*path_line;

	i = 0;
	env_len = ft_strlen(env_name);
	path_line = NULL;
	while ((*envp)[i] != NULL)
	{
		if (ft_strncmp((*envp)[i], env_name, env_len) == 0)
		{
			path_line = (*envp)[i];
			break ;
		}
		i++;
	}
	i = 0;
	if (path_line != NULL)
		while (path_line[i] != '=')
			i++;
	return (path_line + i + 1);
}

char	*get_exec_path(t_ast_node *node, char **all_paths)
{
	char	*part_path;
	char	*exec_path;
	int		i;

	i = 0;
	while (all_paths[i] != NULL)
	{
		part_path = ft_strjoin(all_paths[i], "/");
		exec_path = ft_strjoin(part_path, node->args[0]);
		free(part_path);
		if (access(exec_path, F_OK | X_OK) == 0)
			return (exec_path);
		i++;
	}
	return (NULL);
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
	if (pid == -1)
		printf("fork failed");
	if (pid == 0)
	{
		execve(exec_path, node->args, (char **)*envp);
		perror("execve failed");
	}
	else
		waitpid(pid, NULL, 0);
	return ;
}

void	exec_without_fork(t_ast_node *node, t_envp *envp)
{
	char	**all_paths;
	char	*exec_path;

	all_paths = ft_split(get_env("PATH", envp), ':');
	exec_path = get_exec_path(node, all_paths);
	if (exec_path == NULL)
		return ;
	if (is_builtin(node))
		exec_builtin(node, envp);
	else
	{
		execve(exec_path, node->args, (char **)*envp);
		perror("execve failed");
	}
	return ;
}

void	exec_pipe_child(t_ast_node *node, t_envp *envp, int *p_fd, int isLeft)
{
	if (isLeft)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
		exec_tree(node, envp);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
		exec_tree(node, envp);
	}
	exit(1);
}

// left-to-right iterarive tree traversal

// Start from the root (outermost pipe).

void	exec_pipe(t_ast_node *node, t_envp *envp)
{
	int			p_fd[2];
	pid_t		pid_left;
	pid_t		pid_right;

	if (pipe(p_fd) < 0)
		perror("pipe failed");
	pid_left = fork();
	if (pid_left < 0)
		perror("fork failed");
	if (pid_left == 0)
		exec_pipe_child(node->left, envp, p_fd, 1);
	pid_right = fork();
	if (pid_right < 0)
		perror("fork failed");
	if (pid_right == 0)
		exec_pipe_child(node->right, envp, p_fd, 0);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}

// Go left until reaching the first command (leftmost leaf).
// Execute each command, passing output to the next using pipes.
// Continue right until reaching the last command.

void	exec_tree(t_ast_node *node, t_envp *envp)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		printf("here\n");
		exec_pipe(node, envp);
	}
	else if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			exec_builtin(node, envp);
		else
			exec_bin(node, envp);
	}
}
