/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:43:44 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/06 15:28:51 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_word(char *start, char *input, t_token *token, int expandable, int in_quotes)
{
	if (input > start)
	{
		token->type = TOKEN_WORD;
		token->value = ft_strndup(start, input - start);
		token->expandable = expandable;
		if (!token->value || in_quotes)
		{
			write(STDERR_FILENO, "parse error\n", 13);
			free_token(token);
			return (0);
		}
	}
	return (1);
}

void	update_in_quote(char c, int *in_quote, char *quote_char, int expandable)
{
	if (!(*in_quote) && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		if (c == '\'')
			expandable = 0;
		*quote_char = c;
	}
	else if (*in_quote && (c == *quote_char))
		*in_quote = 0;
}

int	handle_word(t_token *token, char *input, int *pos)
{
	char	*word_start;
	int		in_quote;
	char	quote_char;
	int		expandable;

	expandable = 1;
	word_start = &input[*pos];
	in_quote = 0;
	quote_char = '\0';
	while (input[*pos])
	{
		update_in_quote(input[*pos], &in_quote, &quote_char, expandable);
		if (!in_quote && ft_strchr(" \t\n><|", input[*pos]))
			break ;
		(*pos)++;
	}
	if (!validate_word(word_start, &input[*pos], token, expandable, in_quote))
		return (0);
	return (1);
}

int	handle_operator(t_token *token, char *input, int *pos)
{
	int	advance;

	advance = 0;
	token->type = get_operator_type(&input[*pos], &advance);
	token->value = ft_strndup(&input[*pos], advance);
	if (!token->value || !is_operator_valid(input))
	{
		write(STDERR_FILENO, "parse error\n", 13);
		free_token(token);
		return (0);
	}
	*pos += advance;
	return (1);
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
		{
			if (!handle_operator(token, input, &i))
				return (NULL);
		}
		else
		{
			if (!handle_word(token, input, &i))
				return (NULL);
		}
		ft_lstadd_back(&lexer, ft_lstnew(token));
	}
	return (lexer);
}
