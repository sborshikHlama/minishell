/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:11:18 by iasonov           #+#    #+#             */
/*   Updated: 2024/05/24 17:49:40 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*t;
	unsigned char		tc;

	i = 0;
	t = (const unsigned char *)s;
	tc = (unsigned char)c;
	while (i < n)
	{
		if (t[i] == tc)
			return ((void *)(t + i));
		i++;
	}
	return (NULL);
}
