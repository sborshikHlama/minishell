/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:19:40 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/12 16:34:52 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_ast_node *node)
{
	char	*builtin_commands[9];
	int		i;

	if (!node || node->type != NODE_COMMAND || !node->args)
		return (0);
	builtin_commands[0] = "cd";
	builtin_commands[1] = "echo";
	builtin_commands[2] = "env";
	builtin_commands[3] = "exit";
	builtin_commands[4] = "export";
	builtin_commands[5] = "pwd";
	builtin_commands[6] = "unset";
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(node->args[0], builtin_commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*get_exec_path(t_ast_node *node, char **all_paths)
{
	char	*part_path;
	char	*exec_path;
	int		i;

	i = 0;
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
		exec_path = ft_strjoin(part_path, node->args[0]);
		free(part_path);
		if (access(exec_path, F_OK | X_OK) == 0)
			return (exec_path);
		i++;
	}
	return (NULL);
}

void	restore_fds(int *saved_stdin, int *saved_stdout)
{
	dup2(*saved_stdin, STDIN_FILENO);
	dup2(*saved_stdout, STDOUT_FILENO);
	close(*saved_stdin);
	close(*saved_stdout);
}
