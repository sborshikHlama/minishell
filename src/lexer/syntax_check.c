/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:35:22 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/06 15:19:14 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_valid(char *input)
{
	char	c;

	c = *input;
	input++;
	if (c == *input)
	{
		if (*input == '|')
			return (0);
		input++;
	}
	while (*input && (*input == '\t' || *input == ' '))
			input++;
	if (ft_strchr("><|", *input) || *input == '\0')
			return (0);
	return (1);
}
