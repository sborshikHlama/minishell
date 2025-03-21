/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:43:44 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/21 16:02:57 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_word(char *start, char *input,
	t_token *token, int in_quotes)
{
	if (in_quotes)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (0);
	}
	if (input > start)
	{
		token->type = TOKEN_WORD;
		token->value = ft_strndup(start, input - start);
		if (!token->value)
		{
			ft_putendl_fd("minishell: parse error\n", 2);
			return (0);
		}
	}
	return (1);
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
		update_in_quote(input[*pos], &in_quote, &quote_char, &expandable);
		if (!in_quote && ft_strchr(" \t\n><|", input[*pos]))
			break ;
		(*pos)++;
	}
	if (!validate_word(word_start, &input[*pos], token, in_quote))
	{
		free_token(token);
		return (0);
	}
	token->expandable = expandable;
	return (1);
}

int	handle_operator(t_token *token, char *input, int *pos)
{
	int	advance;

	advance = 0;
	token->type = get_operator_type(&input[*pos], &advance);
	token->value = ft_strndup(&input[*pos], advance);
	if (!token->value || token->type == TOKEN_ERROR
		|| !is_operator_valid(&input[*pos]))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		free_token(token);
		return (0);
	}
	*pos += advance;
	return (1);
}

int	init_token(t_list *token_list, t_token *token, char *input, int *i)
{
	if (ft_strchr("><|&", input[*i]))
	{
		if (!handle_operator(token, input, i))
		{
			ft_lstclear(&token_list, free_token);
			return (0);
		}
		return (1);
	}
	else if (!handle_word(token, input, i))
	{
		ft_lstclear(&token_list, free_token);
		return (0);
	}
	return (1);
}

t_list	*lexer(char *input)
{
	t_list	*token_list;
	t_token	*token;
	int		i;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		while (input[i] && ft_strchr(" \t\n", input[i]))
			i++;
		if (!input[i])
			break ;
		token = create_token();
		if (!token)
			return (NULL);
		if (init_token(token_list, token, input, &i) == 0)
			return (NULL);
		ft_lstadd_back(&token_list, ft_lstnew(token));
	}
	return (token_list);
}
