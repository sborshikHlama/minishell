/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/04 14:37:45 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp_orig)
{
	char		*input;
	t_list		*list;
	t_ast_node	*ast_tree;
	t_envp		envp;

	(void)argc;
	(void)argv;
	if (setup_envp(&envp, envp_orig) == FAILURE)
		return (EXIT_FAILURE);
	while (1)
	{
		input = readline("minishell$> ");
		if (input == NULL)
		{
			free_envp(envp);
			write(STDOUT_FILENO, "exit\n", 5);
			return (0);
		}
		if (*input == '\0')
			continue ;
		if (input)
			add_history(input);
		list = lexer(input);
		display_tokens(list);
		ast_tree = parser(list);
		display_ast(ast_tree, 0);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		write(STDOUT_FILENO, "\n", 1);
		exec_tree(ast_tree, &envp);
		free(input);
	}
}
