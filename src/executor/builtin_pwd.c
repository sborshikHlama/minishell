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

t_status	builtin_pwd(void)
{
	char	cwd[PATH_SIZE];

	if (getcwd(cwd, PATH_SIZE) != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (FAILURE);
	}
	perror("pwd");
	return (SUCCESS);
}
