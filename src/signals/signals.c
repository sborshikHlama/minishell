/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:05:18 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/12 14:33:27 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_sig_status;

static void	signal_handler(int signum)
{
	g_sig_status = signum;
	write(STDOUT_FILENO, "\n", 1);
}

void	init_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
