/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:36:52 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/03 19:47:48 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_export_name(char *name)
{
	write(STDERR_FILENO, "export: not an identifier: ", 28);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, "\n", 2);
}
