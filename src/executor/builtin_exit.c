/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:04:25 by dnovak            #+#    #+#             */
/*   Updated: 2025/02/04 15:20:48 by dnovak           ###   ########.fr       */
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

void	builtin_exit(t_ast_node *node, t_envp envp)
{
	int	exit_status;

	write(STDOUT_FILENO, "exit\n", 6);
	exit_status = 0; /*replace with value of return status of last command*/
	if (node->argc != 1)
	{
		if (ft_isnumeric(node->args[1]) == FALSE)
		{
			write(STDOUT_FILENO, "minishell: exit: ", 18);
			write(STDOUT_FILENO, node->args[1], ft_strlen(node->args[1]));
			write(STDOUT_FILENO, ": numeric argument required\n", 29);
		}
		else
			exit_status = ft_atoi(node->args[1]);
	}
	/*ADD: free all nodes - input and lexer should already be freed*/
	free_envp(envp);
	exit(exit_status);
}
