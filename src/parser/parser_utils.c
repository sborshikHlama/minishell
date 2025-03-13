/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:30:05 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/13 20:42:57 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*create_node(t_node type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		ft_putendl_fd("Error: malloc failed in create_node", STDERR_FILENO);
		return (NULL);
	}
	node->type = type;
	node->args = NULL;
	node->right = NULL;
	node->left = NULL;
	node->redir.append = 0;
	node->redir.infile = NULL;
	node->redir.outfile = NULL;
	node->redir.heredoc_delim = NULL;
	return (node);
}

void	set_redir_value(t_ast_node *node, t_token *token, t_token *next_content)
{
	char	*value;

	value = next_content->value;
	if (token->type == TOKEN_REDIR_IN)
		node->redir.infile = ft_strdup(value);
	else if (token->type == TOKEN_REDIR_APPEND)
	{
		node->redir.outfile = ft_strdup(value);
		node->redir.append = 1;
	}
	else if (token->type == TOKEN_REDIR_OUT)
	{
		node->redir.outfile = ft_strdup(value);
		node->redir.append = 0;
	}
	else if (token->type == TOKEN_REDIR_HEREDOC)
		node->redir.heredoc_delim = ft_strdup(value);
}

t_ast_node	*create_file_node(t_token *temp_token)
{
	t_ast_node	*node;

	if (!temp_token || !temp_token->value)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = ft_strdup(temp_token->value);
	if (!node->args[0])
	{
		free(node->args);
		free(node);
		return (NULL);
	}
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	count_args(t_list *current)
{
	int		counter;
	t_token	*content;

	counter = 0;
	if (!current)
		return (counter);
	while (current)
	{
		content = current->content;
		if (content->type != TOKEN_WORD)
			break ;
		counter++;
		current = current->next;
	}
	return (counter);
}

void	fill_args(t_ast_node *command_node, t_list *list, int argc)
{
	int		i;
	t_list	*current;
	t_token	*content;

	i = 0;
	current = list;
	while (i < argc)
	{
		content = current->content;
		command_node->args[i] = expand(content);
		if (!command_node->args[i])
		{
			while (i > 0)
				free(command_node->args[i--]);
			return ;
		}
		current = current->next;
		free(content->value);
		free(content);
		i++;
	}
	command_node->args[argc] = NULL;
}
