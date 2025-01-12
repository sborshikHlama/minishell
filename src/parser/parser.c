/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:31:45 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/11 10:47:44 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*parse_command(t_list	*list)
{
	t_ast_node	*command_node;
	int			arg_count;

	if (!list)
		return (NULL);
	command_node = create_node(TOKEN_WORD);
	if (!command_node)
		return (NULL);
	arg_count = count_args(list);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
	{
		free(command_node);
		return (NULL);
	}
	fill_args(command_node, list, arg_count);
	return (command_node);
}

t_ast_node	*parse_redir(t_list *list)
{
	t_list		*current;
	t_token		*content;
	t_ast_node	*redir_node;

	current = list;
	redir_node = NULL;
	while (list && list->next)
	{
		content = list->content;
		if (content->type >= TOKEN_REDIR_IN
			&& content->type <= TOKEN_REDIR_HEREDOC)
		{
			redir_node = create_node(content->type);
			redir_node->left = parse_command(current);
			redir_node->right = create_file_node(list->next->content);
			list = list->next->next;
			return (redir_node);
		}
		list = list->next;
	}
	return (parse_command(current));
}

t_ast_node	*parse_pipeline(t_list *list)
{
	t_ast_node	*pipe_node;
	t_list		*last_pipe;
	t_token		*content;
	t_list		*current;

	current = list;
	last_pipe = NULL;
	while (current)
	{
		content = current->content;
		if (content->type == TOKEN_PIPE)
			last_pipe = current;
		current = current->next;
	}
	if (!last_pipe)
		return (parse_redir(list));
	current = list;
	while (current && current->next != last_pipe)
		current = current->next;
	current->next = NULL;
	pipe_node = create_node(TOKEN_PIPE);
	pipe_node->left = parse_pipeline(list);
	pipe_node->right = parse_redir(last_pipe->next);
	return (pipe_node);
}

t_ast_node	*parser(t_list *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}
