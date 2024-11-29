/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:57:53 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/02 14:16:17 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#define ASCII_SIZE 256

char	*ft_strtrim(char const *s1, char const *set)
{
	int		left;
	int		right;
	int		len;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	left = 0;
	while (s1[left] && ft_strchr(set, s1[left]))
		left++;
	right = ft_strlen(s1);
	while (right > left && ft_strchr(set, s1[right - 1]))
		right--;
	len = right - left;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + left, len + 1);
	return (res);
}
