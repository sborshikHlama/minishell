/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:35:22 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/10 15:03:09 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Maybe we don't need to check *input == '\0' 
// 		because it is checked in get_operator_type
int	is_operator_valid(char *input)
{
	char	c;

	c = *input;
	input++;
	if (c == *input)
		input++;
	while (*input && (*input == '\t' || *input == ' '))
		input++;
	if (ft_strchr("><|", *input) || *input == '\0')
		return (0);
	return (1);
}
