/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:47:50 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/04 22:47:54 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Iterates the list ’lst’ and applies the function
 * ’f’ on the content of each node.
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to apply
 * on the list items
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*next;

	if (!lst || !f)
		return ;
	next = lst;
	while (next)
	{
		f(next->content);
		next = next->next;
	}
}
