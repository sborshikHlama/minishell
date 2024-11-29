/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strnstr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iasonov <iasonov@student.42prague.com>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/03 22:24:39 by iasonov		   #+#	#+#			 */
/*   Updated: 2024/06/03 22:24:53 by iasonov		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/**
 * The strnstr() function locates the first occurrence of the 
 * null-terminated string needle in the string haystack, where 
 * not more than len characters are searched. 
 * Characters that appear after a ‘\0’ character are not searched.  
 * Since the strnstr() function is a FreeBSD specific API, it should 
 * only be used when portability is not a concern.
 * @param haystack null-terminated string in which we have to find needle
 * @param needle null-terminated string we need to find in haystack
 * @param len max numbers of characters we're allowed to search
 * @return If needle is an empty string, haystack is returned; 
 * if needle occurs nowhere in haystack, NULL is returned; otherwise a 
 * pointer to the first character of the first occurrence of needle is returned.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	pos;
	size_t	i;

	if (!*needle)
		return ((char *) haystack);
	pos = 0;
	while (haystack[pos] && pos < len)
	{
		if (haystack[pos] == needle[0])
		{
			i = 1;
			while (needle[i] && haystack[pos + i] == needle[i]
				&& pos + i < len)
				i++;
			if (needle[i] == '\0')
				return ((char *)&haystack[pos]);
		}
		pos++;
	}
	return (NULL);
}
