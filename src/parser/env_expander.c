/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:48:42 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/10 11:46:26 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TO DO: use custom get_env instead getenv
char	*get_var_value(char **start, char **end)
{
	char	*var_name;
	char	*var_value;

	while (*end && (ft_isalnum(**end) || **end == '_'))
		(*end)++;
	var_name = ft_substr(*start + 1, 0, *end - *start - 1);
	if (var_name)
		var_value = getenv(var_name);
	else
		var_value = NULL;
	free(var_name);
	if (!var_value)
		var_value = "";
	return (var_value);
}

char	*handle_var(char **start, int exit_status, char *prev)
{
	char	*end;
	char	*var_value;
	char	*temp_result;

	end = *start + 1;
	if (*end == '?')
	{
		var_value = ft_itoa(exit_status);
		end++;
	}
	else if (ft_isalnum(*end) || *end == '_')
		var_value = get_var_value(start, &end);
	else
	{
		var_value = ft_strdup("$");
		end = *start + 1;
	}
	temp_result = ft_strjoin(prev, var_value);
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
			result = handle_var(&start_ptr, 0, result);
		else
			result = handle_plain_text(&start_ptr, result);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*expand(t_token *content)
{
	char	*result;
	char	*str;

	str = unquote_string(content->value);
	if (content->expandable && ft_strchr(str, '$'))
	{
		result = env_expander(str);
		if (!result)
			result = ft_strdup("");
	}
	else
		result = ft_strdup(str);
	if (!result)
		return (NULL);
	free(str);
	return (result);
}
