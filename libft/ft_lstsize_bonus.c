/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:48:22 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/05 00:08:10 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Counts the number of nodes in a list.
 * @param lst: The beginning of the list
 * @return The length of the list
 */
int	ft_lstsize(t_list *lst)
{
	t_list	*next;
	size_t	i;

	next = lst;
	i = 0;
	while (next)
	{
		next = next->next;
		i++;
	}
	return (i);
}
