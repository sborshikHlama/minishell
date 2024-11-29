/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:14:10 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/06 01:04:31 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_len(long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num >= 1)
	{
		len++;
		num /= 10;
	}
	return (len);
}

void	*itoa(long n, char *s, size_t len)
{
	s[len] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	len--;
	while (len > 0)
	{
		s[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	if (s[0] != '-')
		s[0] = (n % 10) + '0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	len;

	len = ft_itoa_len(n);
	s = ft_calloc((len + 1), sizeof(char));
	if (!s)
		return (NULL);
	itoa((long)n, s, len);
	return (s);
}
