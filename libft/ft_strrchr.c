/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:33:17 by iasonov           #+#    #+#             */
/*   Updated: 2024/05/23 22:35:32 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	if ((char) c == '\0')
	{
		while (*s != '\0')
			s++;
		return ((char *) s);
	}
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i - 1] == (char) c)
			return ((char *)(s + i -1));
		i--;
	}
	if (s[0] == (char)c)
		return ((char *)s);
	return (NULL);
}
