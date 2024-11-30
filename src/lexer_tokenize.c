/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:05:25 by aevstign          #+#    #+#             */
/*   Updated: 2024/11/30 19:51:32 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(t_lexer *lexer, t_token *token)
{
	t_token	*current;

	if (!lexer->token_list)
	{
		lexer->token_list = token;
		lexer->token_count++;
		return ;
	}
	current = lexer->token_list;
	while (current->next)
		current = current->next;
	current->next = token;
	lexer->token_count++;
}

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
	if (c == ' ' || c == '\t')
		return (TOKEN_WHITESPACE);
	if (c == '\0')
		return (TOKEN_EOF);
	return (TOKEN_WORD);
}

t_token_type	get_operator_type(char *str, int *advanced)
{
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
	*advanced = 1;
	return (get_char_type(str[0]));
}
