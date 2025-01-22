/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:12:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/01/12 19:10:37 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define MAX_TOKENS 100
# define PATH_SIZE	1024

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

typedef enum e_node
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR
}			t_node;

typedef struct s_ast_node
{
	t_node				type;
	char				**args;
	int					argc;
	int					file_type;
	struct s_ast_node	*right;
	struct s_ast_node	*left;
}	t_ast_node;

typedef struct s_shell_state
{
	t_list	*token_list;
	int		last_exit_code;
}				t_shell_state;

// lexer_utils
t_token_type	get_operator_type(char *str, int *advanced);
t_token_type	get_char_type(char c);
t_token			*create_token(void);
void			free_token(t_token *token);

// lexer
t_list			*lexer(char *input);

// parser_utils
t_ast_node		*create_node(t_node type);
int				count_args(t_list *current);
void			fill_args(t_ast_node *command_node, t_list *list, int argc);
t_ast_node		*create_file_node(t_token *temp_token);

// parser
t_ast_node		*parse_command(t_list	*list);
t_ast_node		*parse_redir(t_list *list);
t_ast_node		*parse_pipeline(t_list *list);
t_ast_node		*parser(t_list *tokens);

// print_debug
void			display_ast(t_ast_node *node, int depth);
void			display_tokens(t_list *lexer);

// executor
void			exec_tree(t_ast_node *node);
void			builtin_cd(t_ast_node *node);
void			builtin_pwd(void);

// executor_utils
int				is_builtin(t_ast_node *node);

#endif
