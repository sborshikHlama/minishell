/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:01:47 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/28 20:05:53 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_sig_status;

int	readline_startup_hook(void)
{
	if (g_sig_status == SIGINT)
	{
		g_sig_status = 0;
		write(STDOUT_FILENO, "\n", 1);
	}
	return (SUCCESS);
}

int	readline_event_hook(void)
{
	if (g_sig_status == SIGINT)
	{
		g_sig_status = 0;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (SUCCESS);
}
