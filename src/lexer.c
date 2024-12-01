/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:43:44 by aevstign          #+#    #+#             */
/*   Updated: 2024/12/01 00:48:25 by iasonov          ###   ########.fr       */
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
	while (input[*pos] && !ft_isspace(input[*pos])
		&& !is_operator(input[*pos]) && !is_quote(input[*pos]))
		(*pos)++;
	token->type = TOKEN_WORD;
	token->value = ft_strndup(&input[word_start], *pos - word_start);
	if (!token->value)
		free_token(token);
}

void	handle_operator(t_token *token, char *input, int *pos)
{
	int	advance;

	advance = 0;
	token->type = get_operator_type(input, &advance);
	token->value = ft_strndup(&input[*pos], advance);
	if (!token->value)
		free_token(token);
	*pos += advance;
}

/*TODO: handle init_lexer failure */
t_list	*lexer(char *input)
{
	t_list	*lexer;
	t_token	*token;
	int		i;

	i = 0;
	lexer = NULL;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
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
		ft_lstadd_back(&lexer, ft_lstnew(token));
	}
	return (lexer);
}
