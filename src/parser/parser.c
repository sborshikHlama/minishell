/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:31:45 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/03 19:17:55 by aevstign         ###   ########.fr       */
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
			redir_node->right = create_file_node(list->next->content);
			current = list->next->next;
			redir_node->left = parse_redir(current);
			return (redir_node);
		}
		list = list->next;
	}
	return (parse_command(current));
}

t_ast_node	*parse_pipeline(t_list *list)
{
	t_list		*temp_list;
	t_list		*next_token;
	t_ast_node	*pipe_node;
	t_token		*content;

	temp_list = list;
	while (list && list->next)
	{
		next_token = list->next;
		content = next_token->content;
		if (content->type == TOKEN_PIPE)
		{
			pipe_node = create_node(TOKEN_PIPE);
			list->next = NULL;
			pipe_node->left = parse_redir(temp_list);
			pipe_node->right = parse_pipeline(next_token->next);
			free(content->value);
			free(content);
			free(next_token);
			return (pipe_node);
		}
		list = list->next;
	}
	return (parse_redir(temp_list));
}

t_ast_node	*parser(t_list *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}
