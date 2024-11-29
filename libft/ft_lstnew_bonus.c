/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:57:08 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/03 23:57:09 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates (with malloc(3)) and returns a new node.
 * The member variable ’content’ is initialized with
 * the value of the parameter ’content’.  The variable
 * ’next’ is initialized to NULL.
 * @param content The content to create the node with.
 * @return The new node
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = (t_list *)malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}
