/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:31:45 by iasonov           #+#    #+#             */
/*   Updated: 2025/03/21 15:16:46 by aevstign         ###   ########.fr       */
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
	current = list;
	if (!last_redirect)
	{
		redirect_node = parse_command(list, envp);
		ft_lstclear(&list, free_token);
		return (redirect_node);
	}
	redirect_node = create_redir_node(&current, last_redirect);
	if (!redirect_node)
		return (NULL);
	redirect_node->left = parse_redir(list, envp);
	return (redirect_node);
}

t_ast_node	*create_pipe_node(t_list *list, t_list *detached, t_envp envp)
{
	t_ast_node	*pipe_node;

	pipe_node = create_node(NODE_PIPE);
	if (!pipe_node)
	{
		ft_lstclear(&list, free_token);
		ft_lstclear(&(detached), free_token);
		return (NULL);
	}
	pipe_node->left = parse_pipeline(list, envp);
	pipe_node->right = parse_redir(detached, envp);
	return (pipe_node);
}

t_ast_node	*parse_pipeline(t_list *list, t_envp envp)
{
	t_ast_node	*pipe_node;
	t_list		*last_pipe;
	t_token		*content;
	t_list		*current;
	t_list		*detached;

	current = list;
	last_pipe = NULL;
	while (current)
	{
		content = current->content;
		if (content->type == TOKEN_PIPE)
			last_pipe = current;
		current = current->next;
	}
	current = list;
	if (!last_pipe)
		return (parse_redir(list, envp));
	while (current && current->next != last_pipe)
		current = current->next;
	current->next = NULL;
	detached = last_pipe->next;
	ft_lstdelone(last_pipe, free_token);
	pipe_node = create_pipe_node(list, detached, envp);
	return (pipe_node);
}

t_ast_node	*parser(t_list *tokens, t_envp envp)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens, envp));
}
