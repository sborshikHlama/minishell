/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 00:31:17 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/01 22:11:24 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*g_buffer;

char	*ft_free(char *remainder, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(remainder, buffer);
	free(remainder);
	return (temp);
}

char	*ft_get_line(char *buffer, char **line)
{
	char	*remainder;
	char	*ptr;
	int		i;

	ptr = buffer;
	remainder = NULL;
	i = 0;
	*line = NULL;
	if (!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	*line = malloc((i + 2) * sizeof(char));
	ft_strlcpy (*line, buffer, i + 2);
	if (i < ft_strlen (buffer))
	{
		ptr += i + 1;
		remainder = (char *) malloc ((ft_strlen (buffer) - i) * sizeof (char));
		ft_strlcpy (remainder, ptr, ft_strlen (buffer) - i);
	}
	free (buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	g_buffer = ft_read (fd, g_buffer);
	if (!g_buffer)
		return (NULL);
	g_buffer = ft_get_line(g_buffer, &line);
	return (line);
}

void	cleanup(void)
{
	if (g_buffer != NULL)
	{
		free(g_buffer);
		g_buffer = NULL;
	}
}
