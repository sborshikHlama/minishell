/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:17:17 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/20 20:26:59 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_input_redir(t_redir *redir)
{
	int		fd;

	fd = open(redir->infile, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

// 644 means you can read and write the file or directory
// and other users can only read it
int	set_output_redir(t_redir *redir)
{
	int	fd;
	int	flags;

	if (redir->append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC ;
	fd = open(redir->outfile, flags, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redirections(t_ast_node *node)
{
	if (node->redir.outfile != NULL)
	{
		if (set_output_redir(&node->redir) < 0)
			return (-1);
	}
	else if (node->redir.infile != NULL)
	{
		if (set_input_redir(&node->redir) < 0)
			return (-1);
	}
	else if (node->redir.heredoc_delim != NULL)
	{
		if (process_heredoc(node) < 0)
			return (-1);
	}
	return (0);
}
