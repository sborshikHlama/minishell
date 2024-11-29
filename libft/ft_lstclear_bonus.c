/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:46:43 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/04 22:47:36 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Deletes and frees the given node and every
 * successor of that node, using the function ’del’
 * and free(3).
 * Finally, the pointer to the list must be set to
 * NULL.
 * @param lst The address of a pointer to a node
 * @param del The address of the function used to 
 * delete the content
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*this;

	if (!lst || !del)
		return ;
	next = *lst;
	while (next)
	{
		this = next;
		next = next->next;
		ft_lstdelone(this, del);
	}
	*lst = NULL;
}
