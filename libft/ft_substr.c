/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:36:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/22 10:49:58 by aevstign         ###   ########.fr       */
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

// int	main(void)
// {
// 	printf("%s", ft_substr("string", 3, 6));
// 	return (0);
// }
