/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:31:59 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/05 21:50:47 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The calloc() function contiguously allocates enough
 * space for count objects that are size bytes of
 * memory each and returns a pointer to the allocated
 * memory. The allocated memory is filled with bytes
 * of value zero.
 * @param count number of objects
 * @param size size of a single object
 * @return If successful, return a pointer to allocated memory.
 * If there is an error, they return a NULL pointer and
 * set errno to ENOMEM.
 */

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	total;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > ((size_t)-1) / size)
		return (NULL);
	total = count * size;
	p = malloc(total);
	if (!p)
		return (NULL);
	ft_bzero(p, total);
	return (p);
}
