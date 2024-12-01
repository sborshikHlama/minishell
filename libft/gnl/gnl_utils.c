/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:17:18 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/01 22:11:38 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*alloc_remainder(char *remainder)
{
	if (remainder == NULL)
	{
		remainder = (char *)malloc(sizeof(char));
		if (remainder == NULL)
			return (NULL);
		*remainder = '\0';
	}
	return (remainder);
}

char	*ft_read(int fd, char *remainder)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	remainder = alloc_remainder(remainder);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free (remainder);
			return (NULL);
		}
		buffer[bytes] = '\0';
		remainder = ft_free(remainder, buffer);
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	free (buffer);
	return (remainder);
}
