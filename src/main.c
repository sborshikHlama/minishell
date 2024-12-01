/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/01 23:16:24 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_list *lexer)
{
	t_list	*current;
	t_token	*content;

	current = lexer;
	while (current)
	{
		content = current->content;
		printf("Type: %d, Value: '%s'\n", content->type, content->value);
		current = current->next;
	}
}

int	main(void)
{
	char	*input;
	t_list	*list;

	while (1)
	{
		write(STDOUT_FILENO, "minishell$> ", 11);
		input = get_next_line(STDIN_FILENO);
		list = lexer(input);
		print_tokens(list);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
	}
}
