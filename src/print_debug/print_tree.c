/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:06:56 by aevstign          #+#    #+#             */
/*   Updated: 2025/01/11 11:09:36 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_command(t_ast_node *node, int depth)
{
	int	i;
	int	j;

	printf("COMMAND Node:\n");
	i = 0;
	while (node->args && node->args[i])
	{
		j = 0;
		while (j < depth)
		{
			printf("    ");
			j++;
		}
		printf("    ├── Argument: %s\n", node->args[i]);
		i++;
	}
}

void	print_redirect(t_ast_node *node)
{
	if (node->args)
	{
		if (strcmp(node->args[0], ">") == 0)
			printf("REDIRECT OUT Node\n");
		else if (strcmp(node->args[0], ">>") == 0)
			printf("REDIRECT APPEND Node\n");
		else if (strcmp(node->args[0], "<") == 0)
			printf("REDIRECT IN Node\n");
		else if (strcmp(node->args[0], "<<") == 0)
			printf("REDIRECT HEREDOC Node\n");
		else
			printf("UNKNOWN REDIRECTION Node\n");
	}
	else
		printf("REDIRECTION Node with NO Operator\n");
}

void	print_node(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	if (node->type == TOKEN_WORD)
		print_command(node, depth);
	else if (node->type == TOKEN_PIPE)
		printf("PIPE Node\n");
	else if (node->type == TOKEN_REDIR_APPEND)
		print_redirect(node);
	else if (node->type == TOKEN_REDIR_HEREDOC)
		print_redirect(node);
	else if (node->type == TOKEN_REDIR_IN)
		print_redirect(node);
	else if (node->type == TOKEN_REDIR_OUT)
		print_redirect(node);
	else
		printf("UNKNOWN Node\n");
}

void	pad(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("    ");
		i++;
	}
}

void	display_ast(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	pad(depth);
	print_node(node, depth);
	if (node->left)
	{
		pad(depth + 1);
		printf("├── Left:\n");
		display_ast(node->left, depth + 2);
	}
	if (node->right)
	{
		pad(depth + 1);
		printf("└── Right:\n");
		display_ast(node->right, depth + 2);
	}
}
