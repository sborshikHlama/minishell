/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:43:44 by aevstign          #+#    #+#             */
/*   Updated: 2024/11/30 19:51:11 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(t_token *token, char *input, int *pos, char quote_type)
{
	token->type = TOKEN_WORD;
	token->value = extract_quoted_string(input, pos, quote_type);
	if (!token->value)
		free_token(token);
}

void	handle_command(t_token *token, char *input, int *pos)
{
	int	word_start;

	word_start = *pos;
	while (input[*pos] && !is_whitespace(input[*pos])
		&& !is_operator(input[*pos]) && !is_quote(input[*pos]))
		(*pos)++;
	token->type = TOKEN_WORD;
	token->value = strndup(&input[word_start], *pos - word_start);
	if (!token->value)
		free_token(token);
}

void	handle_operator(t_token *token, char *input, int *pos)
{
	int	advance;

	advance = 0;
	token->type = get_operator_type(input, &advance);
	token->value = strndup(&input[*pos], advance);
	if (!token->value)
		free_token(token);
	*pos += advance;
}

/*TODO: handle init_lexer failure */
t_lexer	*lexer(char *input)
{
	t_lexer	*lexer;
	t_token	*token;
	int		i;

	lexer = init_lexer();
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		token = create_token();
		if (!token)
			return (NULL);
		if (is_operator(input[i]))
			handle_operator(token, input, &i);
		else if (is_quote(input[i]))
			handle_quotes(token, input, &i, input[i]);
		else
			handle_command(token, input, &i);
		add_token(lexer, token);
	}
	return (lexer);
}

/*********Debug*************************************/
//void print_tokens(t_lexer *lexer)
//{
//    t_token *current = lexer->token_list;

//    printf("Token count: %d\n", lexer->token_count);
//    while (current)
//    {
//        printf("Type: %d, Value: '%s'\n", current->type, current->value);
//        current = current->next;
//    }
//}

//int main(void)
//{
//    char *test_commands[] = {
//        "ls -l",
//        "echo \"hello world\"",
//        "cat < input.txt >> output.txt",
//        "ls -l | grep test",
//        NULL
//    };

//    for (int i = 0; test_commands[i]; i++)
//    {
//        printf("\nTesting: '%s'\n", test_commands[i]);
//        t_lexer *lex = lexer(test_commands[i]);
//        print_tokens(lex);
//        // Add cleanup code
//    }
//    return (0);
//}
