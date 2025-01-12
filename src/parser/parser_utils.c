/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:30:05 by aevstign          #+#    #+#             */
/*   Updated: 2025/01/12 13:06:24 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*create_node(t_node type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		ft_putstr_fd("Error: malloc failed in create_node\n", 2);
		return (NULL);
	}
	node->type = type;
	node->args = NULL;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

t_ast_node	*create_file_node(t_token *temp_token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = temp_token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	free(temp_token);
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
		command_node->args[i] = ft_strdup(content->value);
		if (!command_node->args[i])
		{
			while (i > 0)
			{
				free(command_node->args[i--]);
			}
			return ;
		}
		current = current->next;
		free(content->value);
		free(content);
		i++;
	}
	command_node->args[argc] = NULL;
}
