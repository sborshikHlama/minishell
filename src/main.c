/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/12 18:02:50 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*input;
	t_list		*list;
	t_ast_node	*ast_tree;

	while (1)
	{
		input = readline("minishell$> ");
		if (input == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 4);
			return (0);
		}
		if (*input == '\0')
			continue ;
		list = lexer(input);
		display_tokens(list);
		ast_tree = parser(list);
		display_ast(ast_tree, 0);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		write(STDOUT_FILENO, "\n", 1);
		exec_tree(ast_tree);
		free(input);
	}
}
