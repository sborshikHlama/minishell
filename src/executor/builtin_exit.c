/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:04:25 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/29 14:16:14 by dnovak           ###   ########.fr       */
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

/*
	exit [n]

Exit the minishell, returning a status of n to the shell’s parent. If n is
omitted, the exit status is that of the last command executed.

Errors:
- If n is not numerical, exit the minishell with exit status 2.
- If n is numerical but there is more than one argument, set exit status to 1
  and do not exit the minishell.
*/
void	builtin_exit(t_ast_node *node, t_shell_state *shell_state)
{
	write(STDERR_FILENO, "exit\n", 5);
	if (node->argc != 1)
	{
		if (ft_isnumeric(node->args[1]) == FALSE)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, node->args[1], ft_strlen(node->args[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			shell_state->last_exit_code = 2;
		}
		else if (node->argc > 2)
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			shell_state->last_exit_code = 1;
			return ;
		}
		else
			shell_state->last_exit_code = ft_atoi(node->args[1]);
	}
	free_ast_tree(shell_state->first_node);
	free_envp(*(shell_state->envp));
	rl_clear_history();
	exit(shell_state->last_exit_code);
}
