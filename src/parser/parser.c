/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:31:45 by iasonov           #+#    #+#             */
/*   Updated: 2025/03/19 15:08:38 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*parse_command(t_list	*list, t_envp envp)
{
	t_ast_node	*command_node;
	int			arg_count;

	if (!list)
		return (NULL);
	command_node = create_node(NODE_COMMAND);
	if (!command_node)
		return (NULL);
	arg_count = count_args(list);
	command_node->argc = arg_count;
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
	{
		free(command_node);
		return (NULL);
	}
	fill_args(command_node, list, arg_count, envp);
	return (command_node);
}

t_ast_node	*create_redir_node(t_list **current, t_list *last_redirect)
{
	t_ast_node	*redirect_node;
	t_list		*file_token;

	while ((*current)->next && (*current)->next != last_redirect)
		*current = (*current)->next;
	file_token = (*current)->next;
	if (!file_token || !file_token->next)
		return (NULL);
	(*current)->next = NULL;
	redirect_node = create_node(NODE_REDIR);
	if (!redirect_node)
		return (NULL);
	set_redir_value(redirect_node, file_token->content,
		file_token->next->content);
	return (redirect_node);
}

t_ast_node	*parse_redir(t_list *list, t_envp envp)
{
	t_ast_node	*redirect_node;
	t_list		*last_redirect;
	t_list		*current;

	last_redirect = NULL;
	current = list;
	while (current)
	{
		if (((t_token *)current->content)->type >= TOKEN_REDIR_IN
			&& ((t_token *)current->content)->type <= TOKEN_REDIR_HEREDOC)
			last_redirect = current;
		current = current->next;
	}
	if (!last_redirect)
		return (parse_command(list, envp));
	current = list;
	redirect_node = create_redir_node(&current, last_redirect);
	redirect_node->left = parse_redir(list, envp);
	return (redirect_node);
}

t_ast_node	*parse_pipeline(t_list *list, t_envp envp)
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
		return (parse_redir(list, envp));
	current = list;
	while (current && current->next != last_pipe)
		current = current->next;
	current->next = NULL;
	pipe_node = create_node(NODE_PIPE);
	pipe_node->left = parse_pipeline(list, envp);
	pipe_node->right = parse_redir(last_pipe->next, envp);
	return (pipe_node);
}

t_ast_node	*parser(t_list *tokens, t_envp envp)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens, envp));
}
