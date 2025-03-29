/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:30:05 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/29 12:32:43 by dnovak           ###   ########.fr       */
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

t_ast_node	*create_redir_node(t_list **current, t_list *last_redirect)
{
	t_ast_node	*redirect_node;
	t_list		*file_token;
	t_list		*temp;

	file_token = last_redirect;
	if (!file_token || !file_token->next)
		return (NULL);
	if (*current == last_redirect)
		*current = file_token->next->next;
	else
	{
		temp = *current;
		while (temp->next && temp->next != last_redirect)
			temp = temp->next;
		temp->next = file_token->next->next;
	}
	file_token->next->next = NULL;
	redirect_node = create_node(NODE_REDIR);
	if (!redirect_node)
		return (NULL);
	set_redir_value(redirect_node, file_token->content,
		file_token->next->content);
	ft_lstclear(&(file_token), free_token);
	return (redirect_node);
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

void	fill_args(t_ast_node *command_node, t_list *list, int argc,
	t_shell_state shell_state)
{
	int		i;
	t_list	*current;
	t_token	*content;

	i = 0;
	current = list;
	while (i < argc)
	{
		content = current->content;
		command_node->args[i] = expand(content, shell_state);
		if (!command_node->args[i])
		{
			while (i > 0)
				free(command_node->args[i--]);
			return ;
		}
		current = current->next;
		i++;
	}
	command_node->args[argc] = NULL;
}
