/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:48:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/05 00:07:18 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Iterates the list ’lst’ and applies the function
 * ’f’ on the content of each node.  Creates a new
 * list resulting of the successive applications of
 * the function ’f’.  The ’del’ function is used to
 * delete the content of a node if needed.
 * @param lst The address of a pointer to a node
 * @param f The address of the function to apply on 
 * on the list items
 * @param del The address of the function used to delete
 * the content of a node if needed
 * @return The new list or NULL if allocation fails
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*del)(void *))
{
	t_list	*mapped;
	t_list	*node;
	t_list	*next;

	if (!lst)
		return (NULL);
	mapped = NULL;
	node = NULL;
	next = lst;
	while (next)
	{
		if (!f)
			node = ft_lstnew(next->content);
		else
			node = ft_lstnew(f(next->content));
		if (!node)
		{
			ft_lstclear(&mapped, del);
			return (NULL);
		}
		ft_lstadd_back(&mapped, node);
		next = next->next;
	}
	return (mapped);
}
