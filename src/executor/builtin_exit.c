/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:04:25 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/29 11:12:38 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_isnumeric(char *num)
{
	int	i;

	if (ft_isdigit(num[0]) == 0 && (ft_strchr("-+", num[0]) == NULL
			|| ft_isdigit(num[1]) == 0))
		return (FALSE);
	i = 1;
	while (num[i] != '\0')
	{
		if (ft_isdigit(num[i]) == 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

void	builtin_exit(t_ast_node *node, t_shell_state *shell_state)
{
	write(STDOUT_FILENO, "exit\n", 6);
	if (node->argc != 1)
	{
		if (ft_isnumeric(node->args[1]) == FALSE)
		{
			write(STDOUT_FILENO, "minishell: exit: ", 18);
			write(STDOUT_FILENO, node->args[1], ft_strlen(node->args[1]));
			write(STDOUT_FILENO, ": numeric argument required\n", 29);
		}
		else
			*(shell_state->last_exit_code) = ft_atoi(node->args[1]);
	}
	free_ast_tree(shell_state->first_node);
	free_envp(*(shell_state->envp));
	rl_clear_history();
	exit(*(shell_state->last_exit_code));
}
