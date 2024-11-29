/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:40:50 by iasonov           #+#    #+#             */
/*   Updated: 2024/05/24 21:40:51 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1t;
	const unsigned char	*s2t;

	s1t = (const unsigned char *)s1;
	s2t = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1t[i] != s2t[i])
			return ((unsigned char)s1t[i] - (unsigned char)s2t[i]);
		i++;
	}
	return (0);
}
