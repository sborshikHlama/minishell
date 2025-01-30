/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:48:42 by aevstign          #+#    #+#             */
/*   Updated: 2025/01/30 01:10:58 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_exit_status(char **start, int exit_status, char **prev)
{
	char	*expanded_value;
	char	*result;

	if (*(*start + 1) != '?')
		return (0);
	expanded_value = ft_itoa(exit_status);
	if (!expanded_value)
		return (0);
	result = ft_strjoin(*prev, expanded_value);
	if (!result)
		return (0);
	*prev = result;
	free(expanded_value);
	free(result);
	*start += 2;
	return (1);
}

char	*handle_var(char **start, char *prev)
{
	char	*end;
	char	*var_name;
	char	*var_value;
	char	*temp_result;

	end = *start + 1;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	var_name = ft_substr(*start + 1, 0, end - *start - 1);
	if (!var_name)
		return (NULL);
	var_value = getenv(var_name);
	if (!var_value)
		var_value = "";
	free(var_name);
	temp_result = ft_strjoin(prev, var_value);
	if (!temp_result)
		return (NULL);
	free(prev);
	*start = end;
	return (temp_result);
}

char	*handle_plain_text(char **start, char *prev)
{
	char	*end;
	char	*plain_text;
	char	*temp_result;

	end = *start;
	while (*end && *end != '$')
		end++;
	plain_text = ft_substr(*start, 0, end - *start);
	if (!plain_text)
		return (NULL);
	temp_result = ft_strjoin(prev, plain_text);
	if (!temp_result)
		return (NULL);
	free(prev);
	free(plain_text);
	*start = end;
	return (temp_result);
}

char	*env_expander(const char *arg)
{
	char	*result;
	char	*start_ptr;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	start_ptr = (char *)arg;
	while (*start_ptr)
	{
		if (*start_ptr == '$')
			result = handle_var(&start_ptr, result);
		else
			result = handle_plain_text(&start_ptr, result);
		if (!result)
			return (NULL);
	}
	return (result);
}
