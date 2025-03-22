/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:55:34 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/22 10:49:23 by aevstign         ###   ########.fr       */
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

// int main () {
// 	char str[] = "https://www.tutorialspoint.com";
//    char ch = '.';
//    char *ret;
//    ret = ft_strchr(str, ch);
//    printf("%s", ret);
//    return(0);
// }
