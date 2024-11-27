/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:45:01 by aevstign          #+#    #+#             */
/*   Updated: 2024/11/27 19:19:03 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

t_lexer	*init_lexer(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->token_count = 0;
	lexer->token_list = NULL;
	return (lexer);
}

char	*extract_quoted_string(char *input, int *pos,
	char quote)
{
	int	start;
	int	len;

	start = *pos + 1;
	len = 0;
	while (input[start + len] && input[start + len] != quote)
		len++;
	if (!input[start + len])
		return (NULL);
	*pos = start + len + 1;
	return (strndup(&input[start], len));
}
