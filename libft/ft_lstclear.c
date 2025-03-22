/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 09:40:45 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/22 09:55:24 by aevstign         ###   ########.fr       */
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
