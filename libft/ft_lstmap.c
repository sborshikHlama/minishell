/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:00:43 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/22 10:33:49 by aevstign         ###   ########.fr       */
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
	t_list	*next;
	t_list	*mapped;
	t_list	*node;

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
