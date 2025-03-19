/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:26:10 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/19 15:39:29 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

char	*get_exec_path(t_ast_node *node, char **all_paths)
{
	char	*part_path;
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
		part_path = ft_strjoin(all_paths[i], "/");
		if (part_path == NULL)
			return (NULL);
		exec_path = ft_strjoin(part_path, node->args[0]);
		free(part_path);
		if (access(exec_path, F_OK | X_OK) == 0)
			return (exec_path);
		free(exec_path);
		i++;
	}
	return (NULL);
}

static void	child_process(char *exec_path, t_ast_node *node, t_envp *envp)
{
	int	r;

	r = execve(exec_path, node->args, (char **)*envp);
	if (r < 0)
	{
		perror("execve");
		exit (EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	parent_process(pid_t pid, int *exit_status)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_status = 128 + WTERMSIG(status);
}

void	spawn_binary(char *exec_path, t_ast_node *node, t_envp *envp,
			int *exit_status)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_process(exec_path, node, envp);
	parent_process(pid, exit_status);
}
