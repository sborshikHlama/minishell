/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:18:58 by iasonov           #+#    #+#             */
/*   Updated: 2024/05/27 22:55:01 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	copy_substr(char *dst, const char *src, size_t len, unsigned int start)
{
	size_t	i;

	i = 0;
	while (i < len && src[start + i] != '\0')
	{
		dst[i] = src[start + i];
		i++;
	}
	dst[i] = '\0';
}

char	*allocate(size_t *strlen, unsigned int start, size_t len)
{
	char	*res;

	if (*strlen - start < len)
		*strlen = *strlen - start;
	else
		*strlen = len;
	res = (char *)malloc((*strlen + 1) * sizeof(char));
	return (res);
}

char	*empty_string(void)
{
	char	*empty;

	empty = (char *)malloc(1);
	if (empty)
		empty[0] = '\0';
	return (empty);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (empty_string());
	res = allocate(&strlen, start, len);
	if (res == NULL)
		return (NULL);
	copy_substr(res, s, strlen, start);
	return (res);
}
