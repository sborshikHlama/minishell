/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:17:29 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/06 00:25:20 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	l;
	char	*t;

	l = ft_strlen(src) + 1;
	t = (char *) malloc(l * sizeof(char));
	if (!t)
		return (NULL);
	ft_strlcpy(t, src, l);
	return (t);
}
