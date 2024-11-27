/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:40:26 by aevstign          #+#    #+#             */
/*   Updated: 2024/11/27 19:29:52 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_lexer
{
	t_token	*token_list;
	int		token_count;
}				t_lexer;

/********************lexer_utils**************************/
int				is_operator(char c);
int				is_quote(char c);
int				is_whitespace(char c);
char			*extract_quoted_string(char *input, int *pos, char quote);
t_lexer			*init_lexer(void);
/*********************************************************/

/********************lexer_tokenize***********************/
t_token_type	get_operator_type(char *str, int *advanced);
t_token_type	get_char_type(char c);
void			add_token(t_lexer *lexer, t_token *token);
t_token			*create_token(void);
void			free_token(t_token *token);
/*********************************************************/

#define MAX_TOKENS 100