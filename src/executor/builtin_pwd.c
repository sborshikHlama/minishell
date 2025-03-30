/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:04:45 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/04 23:54:53 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	pwd

Print the absolute pathname of the current working directory.

Error:
The return status is zero unless an error is encountered while determining
the name of the current directory.
*/
t_status	builtin_pwd(void)
{
	char	cwd[PATH_SIZE];

	if (getcwd(cwd, PATH_SIZE) != NULL)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (SUCCESS);
	}
	perror("minishell: pwd");
	return (FAILURE);
}
