/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:12:22 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/29 16:47:06 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_quote(char **start, char *prev, char quote_char)
{
	char	*end;
	char	*quote_text;
	char	*temp_result;

	end = *start + 1;
	while (*end != '\0' && *end != quote_char)
		++end;
	quote_text = ft_substr(*start, 1, end - *start - 1);
	if (!quote_text)
		return (NULL);
	temp_result = ft_strjoin(prev, quote_text);
	free(quote_text);
	free(prev);
	if (!temp_result)
		return (NULL);
	*start = ++end;
	return (temp_result);
}

static char	*handle_unquote(char **start, char *prev)
{
	char	*end;
	char	*plain_text;
	char	*temp_result;

	end = *start;
	while (*end != '\0')
	{
		if (*end == '\'' || *end == '\"')
			break ;
		++end;
	}
	plain_text = ft_substr(*start, 0, end - *start);
	if (!plain_text)
		return (NULL);
	temp_result = ft_strjoin(prev, plain_text);
	free(plain_text);
	free(prev);
	if (!temp_result)
		return (NULL);
	*start = end;
	return (temp_result);
}

char	*unquote_string(char *str)
{
	char	*new_str;
	char	*start_ptr;

	new_str = ft_strdup("");
	if (new_str == NULL)
		return (NULL);
	start_ptr = str;
	while (*start_ptr)
	{
		if (*start_ptr == '\'' || *start_ptr == '\"')
			new_str = handle_quote(&start_ptr, new_str, *start_ptr);
		else
			new_str = handle_unquote(&start_ptr, new_str);
		if (new_str == NULL)
			return (NULL);
	}
	return (new_str);
}
