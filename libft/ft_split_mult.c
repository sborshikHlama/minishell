/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mult.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:33:39 by iasonov           #+#    #+#             */
/*   Updated: 2024/11/09 02:35:48 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	count_splits_mult(char const *s, char *charset)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (!is_delimiter(*s, charset) && !in_substring)
		{
			in_substring = 1;
			count++;
		}
		else if (is_delimiter(*s, charset))
		{
			in_substring = 0;
		}
		s++;
	}
	return (count);
}

static int	len(const char *s, char *charset, int i, int start)
{
	if (!is_delimiter(s[i], charset))
		i = i + 1;
	if (is_delimiter(s[i], charset) || s[i] == '\0')
	{
		return (i - start);
	}
	else
	{
		return (i - start + 1);
	}
}

int	do_split_mult(char **res, char const *s, char *charset, int count)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = -1;
	while (s[i] != '\0')
	{
		if (!is_delimiter(s[i], charset) && start == -1)
			start = i;
		else if ((is_delimiter(s[i], charset)
				|| s[i + 1] == '\0') && start != -1)
		{
			if (!do_copy(&res[j], len(s, charset, i, start), s, start))
				return (0);
			start = -1;
			j++;
		}
		i++;
	}
	if (j < count && !do_copy(&res[j],
			len(s, charset, i, start), s, start))
		return (0);
	return (1);
}

char	**ft_split_mult(char *str, char *charset)
{
	char	**res;
	int		count;
	int		i;

	if (str == NULL || charset == NULL)
		return (NULL);
	count = count_splits_mult(str, charset);
	res = (char **)malloc((count + 1) * sizeof(char *));
	if (res == NULL)
	{
		return (NULL);
	}
	if (!do_split_mult(res, str, charset, count))
	{
		i = 0;
		while (i < count)
		{
			free(res[i]);
			i++;
		}
		free(res);
		return (NULL);
	}
	res[count] = NULL;
	return (res);
}
