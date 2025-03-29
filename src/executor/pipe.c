/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:13:21 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/29 11:18:54 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child_right(t_ast_node *node, int *p_fd,
			t_shell_state *shell_state)
{
	close(p_fd[1]);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	exec_tree(node, shell_state);
	free_ast_tree(shell_state->first_node);
	free_envp(*(shell_state->envp));
	rl_clear_history();
	exit(0);
}

static void	exec_child_left(t_ast_node *node, int *p_fd,
				t_shell_state *shell_state)
{
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	exec_tree(node, shell_state);
	free_ast_tree(shell_state->first_node);
	free_envp(*(shell_state->envp));
	rl_clear_history();
	exit(0);
}

void	exec_pipe(t_ast_node *node, t_shell_state *shell_state)
{
	int		p_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(p_fd) < 0)
		perror("pipe");
	pid_left = fork();
	if (pid_left < 0)
		perror("fork");
	if (pid_left == 0)
		exec_child_left(node->left, p_fd, shell_state);
	pid_right = fork();
	if (pid_right < 0)
		perror("fork");
	if (pid_right == 0)
		exec_child_right(node->right, p_fd, shell_state);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}
