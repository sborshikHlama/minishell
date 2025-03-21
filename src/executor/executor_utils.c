/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:19:40 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/21 16:05:35 by aevstign         ###   ########.fr       */
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

void	restore_fds(int *saved_stdin, int *saved_stdout)
{
	dup2(*saved_stdin, STDIN_FILENO);
	dup2(*saved_stdout, STDOUT_FILENO);
	close(*saved_stdin);
	close(*saved_stdout);
}

void	free_all_paths(char **all_paths)
{
	int	i;

	i = 0;
	while (all_paths[i] != NULL)
	{
		free(all_paths[i]);
		++i;
	}
	free(all_paths);
}

void	free_ast_tree(t_ast_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->args)
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	if (node->redir.heredoc_delim)
		free(node->redir.heredoc_delim);
	if (node->redir.infile)
		free(node->redir.infile);
	if (node->redir.outfile)
		free(node->redir.outfile);
	free_ast_tree(node->left);
	free_ast_tree(node->right);
	free(node);
}
