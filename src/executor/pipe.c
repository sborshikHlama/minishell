/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:13:21 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/11 09:22:30 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exit(0);
}

void	exec_pipe(t_ast_node *node, t_envp *envp)
{
	int			p_fd[2];
	pid_t		pid_left;
	pid_t		pid_right;

	if (pipe(p_fd) < 0)
		perror("pipe");
	pid_left = fork();
	if (pid_left < 0)
		perror("fork");
	if (pid_left == 0)
		exec_pipe_child(node->left, envp, p_fd, 1);
	pid_right = fork();
	if (pid_right < 0)
		perror("fork");
	if (pid_right == 0)
		exec_pipe_child(node->right, envp, p_fd, 0);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}
