/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:43:44 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/01 19:23:10 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	validate_word(char *start, char *input, t_token *token, int expandable)
{
	if (input > start)
	{
		token->type = TOKEN_WORD;
		token->value = ft_strndup(start, input - start);
		token->expandable = expandable;
		if (!token->value)
			free_token(token);
	}
}

void	update_in_quote(char c, int *in_quote, char *quote_char)
{
	if (!(*in_quote) && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
	else if (*in_quote && (c == *quote_char))
		*in_quote = 0;
}

void	handle_word(t_token *token, char *input, int *pos)
{
	char	*word_start;
	int		in_quote;
	char	quote_char;
	int		expandable;

	word_start = &input[*pos];
	in_quote = 0;
	quote_char = '\0';
	while (input[*pos])
	{
		update_in_quote(input[*pos], &in_quote, &quote_char);
		if (!in_quote && ft_strchr(" \t\n><|", input[*pos]))
			break ;
		if (in_quote && quote_char == '\'')
			expandable = 0;
		(*pos)++;
	}
	validate_word(word_start, &input[*pos], token, expandable);
}

void	handle_operator(t_token *token, char *input, int *pos)
{
	int	advance;

	advance = 0;
	token->type = get_operator_type(&input[*pos], &advance);
	token->value = ft_strndup(&input[*pos], advance);
	if (!token->value)
		free_token(token);
	*pos += advance;
}

t_list	*lexer(char *input)
{
	t_list	*lexer;
	t_token	*token;
	int		i;

	i = 0;
	lexer = NULL;
	while (input[i])
	{
		while (input[i] && ft_strchr(" \t\n", input[i]))
			i++;
		if (!input[i])
			break ;
		token = create_token();
		if (!token)
			return (NULL);
		if (ft_strchr("><|", input[i]))
			handle_operator(token, input, &i);
		else
			handle_word(token, input, &i);
		ft_lstadd_back(&lexer, ft_lstnew(token));
	}
	return (lexer);
}
