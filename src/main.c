/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/03/12 14:33:18 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

sig_atomic_t	g_sig_status;

int	readline_hook(void)
{
	if (g_sig_status == SIGINT || g_sig_status == SIGQUIT)
	{
		g_sig_status = 0;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp_orig)
{
	int			exit_status;
	char		*input;
	t_list		*list;
	t_ast_node	*ast_tree;
	t_envp		envp;

	(void)argc;
	(void)argv;
	init_signals();
	rl_event_hook = &readline_hook;
	exit_status = 0;
	if (setup_envp(&envp, envp_orig) == FAILURE)
		return (EXIT_FAILURE);
	while (1)
	{
		input = readline("minishell$> ");
		if (input == NULL)
		{
			free_envp(envp);
			write(STDOUT_FILENO, "exit\n", 5);
			return (EXIT_SUCCESS);
		}
		if (*input == '\0')
			continue ;
		if (input)
			add_history(input);
		list = lexer(input);
		if (DEBUG_STATUS)
			display_tokens(list);
		ast_tree = parser(list);
		if (DEBUG_STATUS)
		{
			display_ast(ast_tree, 0);
			write(STDOUT_FILENO, "Entered: ", 9);
			write(STDOUT_FILENO, input, ft_strlen(input));
			write(STDOUT_FILENO, "\n", 1);
		}
		exec_tree(ast_tree, &envp, &exit_status);
		free(input);
	}
}
