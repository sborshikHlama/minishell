/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:12:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/04 14:36:00 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX_TOKENS 100
# define PATH_SIZE 1024

typedef char			**t_envp;

typedef enum e_status
{
	SUCCESS,
	FAILURE,
}						t_status;

typedef enum e_bool
{
	FALSE,
	TRUE,
}						t_bool;

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
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	int					expandable;
}						t_token;

typedef enum e_node
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR
}						t_node;

typedef struct s_ast_node
{
	t_node				type;
	char				**args;
	int					argc;
	int					file_type;
	struct s_ast_node	*right;
	struct s_ast_node	*left;
}						t_ast_node;

typedef struct s_shell_state
{
	t_list				*token_list;
	int					last_exit_code;
}						t_shell_state;

// environ_utils
void					free_envp(t_envp envp);
int						envp_size(t_envp envp);

// environ
t_status				setup_envp(t_envp *dest, t_envp orig);

// lexer_utils
t_token_type			get_operator_type(char *str, int *advanced);
t_token_type			get_char_type(char c);
t_token					*create_token(void);
void					free_token(t_token *token);

// lexer
t_list					*lexer(char *input);

// parser_utils
t_ast_node				*create_node(t_node type);
int						count_args(t_list *current);
void					fill_args(t_ast_node *command_node, t_list *list,
							int argc);
t_ast_node				*create_file_node(t_token *temp_token);

// parser
t_ast_node				*parse_command(t_list *list);
t_ast_node				*parse_redir(t_list *list);
t_ast_node				*parse_pipeline(t_list *list);
t_ast_node				*parser(t_list *tokens);

// print_debug
void					display_ast(t_ast_node *node, int depth);
void					display_tokens(t_list *lexer);

// executor
void					exec_tree(t_ast_node *node, t_envp *envp);
void					builtin_cd(t_ast_node *node);
void					builtin_pwd(void);
t_status				builtin_echo(t_ast_node *node);
t_status				builtin_env(t_envp envp);
t_status				builtin_export(t_ast_node *node, t_envp *envp);
t_status				builtin_unset(t_ast_node *node, t_envp *envp);

// executor_utils
int						is_builtin(t_ast_node *node);

// builtin_utils (export/unset)
t_bool					isname(char *name);
t_bool					check_envp(char *name, t_envp envp);

// builtin_errors
void					error_export_name(char *name);
void					error_unset_args(void);
void					error_unset_name(char *name);

// env_expander
char					*env_expander(const char *arg);

#endif
