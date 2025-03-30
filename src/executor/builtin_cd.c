/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:48:37 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/29 18:32:50 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	cd [directory]

Change the current working directory to directory. If directory is not
supplied, the value of the HOME shell variable is used.

If ‘..’ appears in directory, it is processed by removing the immediately
preceding pathname component, back to a slash or the beginning of directory.

The return status is zero if the directory is successfully changed, non-zero
otherwise. 
*/
t_status	builtin_cd(t_ast_node *node, t_envp envp)
{
	char	*path;

	if (node->argc > 2)
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		return (FAILURE);
	}
	else if (node->argc < 2)
	{
		path = ft_getenv("HOME", envp);
		if (path == NULL)
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
			return (FAILURE);
		}
	}
	else
		path = node->args[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (FAILURE);
	}
	return (SUCCESS);
}
