/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:05:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/07 10:48:50 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_NULL;
	token->value = NULL;
	token->next = NULL;
	return (token);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	if (token->next)
		free(token->next);
	free(token);
}

t_token_type	get_char_type(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (c == '"')
		return (TOKEN_DOUBLE_QUOTE);
	if (c == '>')
		return (TOKEN_REDIR_OUT);
	if (c == '<')
		return (TOKEN_REDIR_IN);
	return (TOKEN_ERROR);
}

t_token_type	get_operator_type(char *str, int *advanced)
{
	if (!str || !str[1])
		return (TOKEN_ERROR);
	if (str[0] == '>' && str[1] == '>')
	{
		*advanced = 2;
		return (TOKEN_REDIR_APPEND);
	}
	if (str[0] == '<' && str[1] == '<')
	{
		*advanced = 2;
		return (TOKEN_REDIR_HEREDOC);
	}
	if ((str[0] == '|' && str[1] == '|') || (str[0] == '&' && str[1] == '&'))
	{
		*advanced = 2;
		return (TOKEN_ERROR);
	}
	*advanced = 1;
	return (get_char_type(str[0]));
}
