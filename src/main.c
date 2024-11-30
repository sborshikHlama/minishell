/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/11/30 19:48:23 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_tokens(t_lexer *lexer)
{
    t_token *current = lexer->token_list;

    printf("Token count: %d\n", lexer->token_count);
    while (current)
    {
        printf("Type: %d, Value: '%s'\n", current->type, current->value);
        current = current->next;
    }
}


int	main(void)
{
	char	*input;

	while (1)
	{
		write(STDOUT_FILENO, "minishell$> ", 11);
		input = get_next_line(STDIN_FILENO);
		t_lexer *lex = lexer(input);
		print_tokens(lex);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
	}
}
