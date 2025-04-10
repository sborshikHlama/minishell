/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:12:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/29 18:00:18 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// FOR: signals
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 199309L
# endif

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_TOKENS 100
# define PATH_SIZE 1024
# define DEBUG_STATUS 0

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
	int					expandable;
}						t_token;

typedef enum e_node
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR
}						t_node;

typedef struct s_redir
{
	char				*infile;
	char				*outfile;
	int					append;
	char				*heredoc_delim;
}						t_redir;

typedef struct s_ast_node
{
	t_node				type;
	char				**args;
	int					argc;
	int					file_type;
	struct s_ast_node	*right;
	struct s_ast_node	*left;
	t_redir				redir;
}						t_ast_node;

typedef struct s_shell_state
{
	t_list				*token_list;
	t_envp				*envp;
	t_ast_node			*first_node;
	int					last_exit_code;
}						t_shell_state;

typedef struct s_quote_state
{
	t_bool				in_quote;
	t_bool				expandable;
	char				quote_char;
}						t_quote_state;

// environ_utils
void					free_envp(t_envp envp);
int						envp_size(t_envp envp);
char					*ft_getenv(const char *name, t_envp envp);

// environ
t_status				setup_envp(t_envp *dest);

//readline hooks
int						readline_startup_hook(void);
int						readline_event_hook(void);

// syntax_check
int						is_operator_valid(char *input);

// lexer_utils
t_token_type			get_operator_type(char *str, int *advanced);
t_token_type			get_char_type(char c);
t_token					*create_token(void);
void					free_token(void *content);
void					update_in_quote(char c, int *in_quote,
							char *quote_char, int *expandable);

// lexer
t_list					*lexer(char *input);

// parser_utils
t_ast_node				*create_node(t_node type);
int						count_args(t_list *current);
void					fill_args(t_ast_node *command_node, t_list *list,
							int argc);
t_ast_node				*create_redir_node(t_list **current,
							t_list *last_redirect);
char					*set_redir_value(t_ast_node *node, t_token *token,
							t_token *next_content);
void					free_ast_tree(t_ast_node *node);

// parser

t_ast_node				*parser(t_list *tokens, t_shell_state shell_state);
t_ast_node				*parse_pipeline(t_list *list,
							t_shell_state shell_state);

// print_debug
void					display_ast(t_ast_node *node, int depth);
void					display_tokens(t_list *lexer);

// executor
void					exec_tree(t_ast_node *node, t_shell_state *shell_state);
t_status				builtin_cd(t_ast_node *node, t_envp envp);
t_status				builtin_pwd(void);
t_status				builtin_echo(t_ast_node *node);
t_status				builtin_env(t_envp envp);
t_status				builtin_export(t_ast_node *node, t_envp *envp);
t_status				builtin_unset(t_ast_node *node, t_envp *envp);
void					builtin_exit(t_ast_node *node,
							t_shell_state *shell_state);

// executor_utils
int						is_builtin(t_ast_node *node);
void					free_ast_tree(t_ast_node *node);
void					free_all_paths(char **all_paths);

// binary
char					*get_exec_path(t_ast_node *node, char **all_paths);
void					spawn_binary(char *exec_path, t_ast_node *node,
							t_shell_state *shell_state);

// builtin_utils (export/unset)
t_bool					isname(char *name);
t_bool					check_envp(char *name, t_envp envp);
t_status				print_envp(t_envp envp);
t_status				envp_replace_value(char *new_var, char *name,
							t_envp *envp);
t_status				envp_add_new(char *new_var, t_envp *envp);

// builtin_errors
void					error_export_name(char *name);

// env_expander
char					*env_expander(char *input, t_shell_state *shell_state);

// unquote_string
char					*unquote_string(char *str);

// pipe
void					exec_pipe(t_ast_node *node, t_shell_state *shell_state);

// redirection
int						handle_redirections(t_ast_node *node);
void					restore_fds(int *saved_stdin, int *saved_stdout);

// heredoc
int						process_heredoc(t_ast_node *node);

// signals
t_status				init_signals(void);
void					reset_quit_signal(void);
void					ignore_int_signal(void);
void					setup_int_signal(void);

#endif
