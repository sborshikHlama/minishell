/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:12:25 by aevstign          #+#    #+#             */
/*   Updated: 2024/12/03 16:36:24 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"

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

typedef struct s_command
{

}				t_command;

typedef struct s_ast_node
{
	t_token_type		type;
	char				**args;
	int					file_type;
	struct s_ast_node	*right;
	struct s_ast_node	*left;
}	t_ast_node;

// lexer_utils

t_token_type	get_operator_type(char *str, int *advanced);
t_token_type	get_char_type(char c);
t_token			*create_token(void);
void			free_token(t_token *token);

// lexer
t_list			*lexer(char *input);

// parser_utils
t_ast_node		*create_node(t_token_type type);
int				count_args(t_list *current);
void			fill_args(t_ast_node *command_node, t_list *list, int argc);
t_ast_node		*create_file_node(t_token *temp_token);

// parser
t_ast_node		*parse_command(t_list	*list);
t_ast_node		*parse_redir(t_list *list);
t_ast_node		*parse_pipeline(t_list *list);
t_ast_node		*parser(t_list *tokens);

#endif
