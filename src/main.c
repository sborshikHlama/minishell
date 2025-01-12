/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/11 19:05:24 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_input(void)
{
	char	*result;

	result = get_next_line(STDIN_FILENO);
	if (!result)
	{
		write(STDOUT_FILENO, "minishell: error reading input\n", 32);
		return (NULL);
	}
	return (result);
}

int	main(void)
{
	char		*input;
	t_list		*list;
	t_ast_node	*ast_tree;

	while (1)
	{
		write(STDOUT_FILENO, "minishell$> ", 11);
		input = read_input();
		if (!input)
			continue ;
		list = lexer(input);
		display_tokens(list);
		ast_tree = parser(list);
		display_ast(ast_tree, 0);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
	}
}
