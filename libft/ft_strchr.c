/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:10:00 by iasonov           #+#    #+#             */
/*   Updated: 2024/05/23 22:23:55 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*t;

	t = (char *) s;
	while (*t != '\0')
	{
		if (*t == (char) c)
			return (t);
		t++;
	}
	if ((char) c == '\0')
		return (t);
	return (NULL);
}
