/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:12:06 by aevstign          #+#    #+#             */
/*   Updated: 2025/03/22 10:46:35 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

// int main () {
//    int i, n;
//    int *a;

//    printf("Number of elements to be entered:");
//    scanf("%d",&n);

//    a = (int*)ft_calloc(n, sizeof(int));
//    printf("Enter %d numbers:\n",n);
//    for( i=0 ; i < n ; i++ ) {
//       scanf("%d",&a[i]);
//    }

//    printf("The numbers entered are: ");
//    for( i=0 ; i < n ; i++ ) {
//       printf("%d ",a[i]);
//    }
//    free( a );
//    return(0);
// }