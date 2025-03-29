/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:26:10 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/29 18:42:22 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile sig_atomic_t	g_sig_status;

static char	*build_path(char *bin, char *name)
{
	char	*part_path;
	char	*result;

	part_path = ft_strjoin(bin, "/");
	if (!part_path)
		return (NULL);
	result = ft_strjoin(part_path, name);
	free(part_path);
	if (!result)
		return (NULL);
	return (result);
}

char	*get_exec_path(t_ast_node *node, char **all_paths)
{
	char	*exec_path;
	int		i;

	i = 0;
	if (all_paths == NULL)
		return (NULL);
	if (node->args[0][0] == '/' || ft_strchr(node->args[0], '/'))
	{
		if (access(node->args[0], F_OK | X_OK) == 0)
			return (ft_strdup(node->args[0]));
		else
			return (NULL);
	}
	while (all_paths[i] != NULL)
	{
		exec_path = build_path(all_paths[i], node->args[0]);
		if (!exec_path)
			return (NULL);
		if (access(exec_path, F_OK | X_OK) == 0)
			return (exec_path);
		free(exec_path);
		i++;
	}
	return (NULL);
}

static void	child_process(char *exec_path, t_ast_node *node,
		t_shell_state *shell_state)
{
	int	r;

	reset_quit_signal();
	r = execve(exec_path, node->args, (char **)*(shell_state->envp));
	if (r < 0)
	{
		perror("execve");
		free(exec_path);
		free_ast_tree(shell_state->first_node);
		free_envp(*(shell_state->envp));
		rl_clear_history();
		exit(1);
	}
	exit(0);
}

void	parent_process(pid_t pid, int *exit_status)
{
	int	status;
	int	w;

	ignore_int_signal();
	w = waitpid(pid, &status, 0);
	setup_int_signal();
	if (w == -1)
	{
		*exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		*exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			g_sig_status = SIGINT;
		if (WTERMSIG(status) == SIGQUIT && __WCOREDUMP(status))
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}
}

void	spawn_binary(char *exec_path, t_ast_node *node,
			t_shell_state *shell_state)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_process(exec_path, node, shell_state);
	parent_process(pid, &(shell_state->last_exit_code));
}
