/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:50:13 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/13 23:25:49 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Open a temporary file for storing user input.
// Read each line using get_next_line(STDIN_FILENO).
// Compare the line with the delimiter:
// If it matches, stop reading.
// Otherwise, write it to the temporary file.
// Close the file and redirect stdin (dup2()).
// Execute the command using the temporary file as input.

static void	read_heredoc_input(int fd, char *delim)
{
	char	*line;
	int		len;

	while (1)
	{
		line = readline(NULL);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static int	write_to_file(char *temp_file, char *delim)
{
	int	fd;

	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	read_heredoc_input(fd, delim);
	close(fd);
	return (0);
}

int	process_heredoc(t_ast_node *node)
{
	char	*temp_file;
	char	*delim;
	int		fd;

	temp_file = "/tmp/minishell_heredoc";
	delim = node->redir.heredoc_delim;
	if (write_to_file(temp_file, delim) < 0)
		return (-1);
	fd = open(temp_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
