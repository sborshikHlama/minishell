/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:04:45 by aevstign          #+#    #+#             */
/*   Updated: 2025/01/12 19:12:38 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(void)
{
	char	cwd[PATH_SIZE];

	if (getcwd(cwd, PATH_SIZE) != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return ;
	}
	write(1, "pwd: error", 10);
}
