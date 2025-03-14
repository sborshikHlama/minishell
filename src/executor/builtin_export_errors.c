/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:36:52 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/05 00:45:59 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_export_name(char *name)
{
	write(STDERR_FILENO, "minishell: export: `", 21);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
}
