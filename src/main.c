/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/03 19:12:58 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[7];

	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "REDIRECT_IN";
	token_type_names[3] = "REDIRECT_OUT";
	token_type_names[4] = "REDIRECT_APPEND";
	token_type_names[5] = "REDIRECT_HEREDOC";
	token_type_names[6] = "TOKEN_ENV_VAR";
	if (type >= 0 && type < 7)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	display_tokens(t_list *lexer)
{
	t_list	*current;
	t_token	*token;

	current = lexer;
	while (current)
	{
		token = current->content;
		printf("Token: \033[0;36m %-20s \033[0m |\t \
			Type: \033[0;35m %-18s \033[0m \n",
			token->value, get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		current = current->next;
	}
}

void	print_node(t_ast_node *node)
{
	if (node->type == TOKEN_WORD)
		printf("└── Node Type: WORD, Token Value: %s\n", node->args[0]);
	else if (node->type == TOKEN_PIPE)
		printf("└── Node Type: PIPE\n");
	else if (node->type == TOKEN_REDIR_IN)
		printf("└── Node Type: REDIRECT IN\n");
	else if (node->type == TOKEN_REDIR_OUT)
		printf("└── Node Type: REDIRECT OUT\n");
	else if (node->type == TOKEN_REDIR_APPEND)
		printf("└── Node Type: REDIRECT APPEND\n");
	else if (node->type == TOKEN_REDIR_HEREDOC)
		printf("└── Node Type: REDIRECT HEREDOC\n");
	else
		printf("└── Node Type: UNKNOWN\n");
}

void	display_ast(t_ast_node *node, int depth)
{
	int	i;

	i = 0;
	if (node == NULL)
		return ;
	display_ast(node->left, depth + 1);
	while (i++ < depth)
		printf("	");
	print_node(node);
	display_ast(node->right, depth + 1);
}


int	main(void)
{
	char		*input;
	t_list		*list;
	t_ast_node	*ast_tree;

	while (1)
	{
		write(STDOUT_FILENO, "minishell$> ", 11);
		input = get_next_line(STDIN_FILENO);
		list = lexer(input);
		display_tokens(list);
		ast_tree = parser(list);
		display_ast(ast_tree, 0);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
	}
}
