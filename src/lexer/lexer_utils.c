/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:45:01 by aevstign          #+#    #+#             */
/*   Updated: 2024/12/01 23:17:30 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
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
