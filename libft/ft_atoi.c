/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:05:48 by iasonov           #+#    #+#             */
/*   Updated: 2024/06/05 16:06:26 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

/**
 * The string may begin with an arbitrary amount of white space (as
 * determined by isspace(3)) followed by a single optional `+' or `-' sign.
 * @param str original string
 * @param i current index
 * @return sign
 */
int	determine_sign(const char *str, long *i)
{
	int	sign;
	int	sign_count;

	sign = 1;
	sign_count = 0;
	while (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -sign;
		(*i)++;
		sign_count++;
		if (sign_count > 1)
			return (0);
	}
	return (sign);
}

long	do_atoi(const char *str, long *i)
{
	long	result;

	result = 0;
	while (ft_isdigit(str[*i]))
	{
		result = (result * 10) + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

/**
 * The documentation is not clear on that part but
 * the program should consider as invalid string a string
 * with multiple signes in it. Refer to the determine_sign
 * function.
 * Standart library atoi should:
 * - ignore leading whitespaces;
 * - it should handle optional initial sign;
 * - it should convert the subsequent characters until a
 *   non-digit character is encountered;
 * @param str string to convert
 * @return converted string as an int
 */
long	ft_atoi(const char *str)
{
	long	i;
	int		sign;
	long	result;

	i = 0;
	while (is_space(str[i]))
		i++;
	sign = determine_sign(str, &i);
	result = do_atoi(str, &i);
	return (result * sign);
}
