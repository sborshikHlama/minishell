/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:12:25 by aevstign          #+#    #+#             */
/*   Updated: 2024/12/01 22:12:00 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft/libft.h"

# define MAX_TOKENS 100

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_WHITESPACE,
	TOKEN_EOF,
	TOKEN_ERROR,
	TOKEN_NULL,
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

// lexer_utils
int				is_operator(char c);
int				is_quote(char c);
int				is_whitespace(char c);
char			*extract_quoted_string(char *input, int *pos, char quote);

// lexer_tokenize
t_token_type	get_operator_type(char *str, int *advanced);
t_token_type	get_char_type(char c);
t_token			*create_token(void);
void			free_token(t_token *token);

// lexer
t_list			*lexer(char *input);
#endif
