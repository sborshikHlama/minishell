/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:19:50 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/22 10:45:49 by aevstign         ###   ########.fr       */
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

// int main () {
//    const char str[] = "https://www.tutorialspoint.com";
//    const char ch = '.';
//    char *ret;

//    ret = ft_memchr(str, ch, strlen(str));

//    printf("String after |%c| is - |%s|\n", ch, ret);

//    return(0);
// }
