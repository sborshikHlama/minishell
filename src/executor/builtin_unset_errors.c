/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:36:52 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/01 22:38:02 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_unset_args(void)
{
	write(STDERR_FILENO, "unset: not enough arguments\n", 29);
}

void	error_unset_name(char *name)
{
	write(STDERR_FILENO, "unset: ", 8);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, ": invalid parameter name\n", 26);
}
