/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:12:36 by dnovak            #+#    #+#             */
/*   Updated: 2025/03/29 16:48:59 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_value(char **start, char **end, t_envp envp)
{
	char	*var_name;
	char	*var_value;

	while (*end && (ft_isalnum(**end) || **end == '_'))
		(*end)++;
	var_name = ft_substr(*start + 1, 0, *end - *start - 1);
	if (var_name)
		var_value = ft_getenv(var_name, envp);
	else
		var_value = NULL;
	free(var_name);
	if (!var_value)
		var_value = "";
	return (ft_strdup(var_value));
}

static char	*handle_var(char **start, char *prev, t_shell_state *shell_state)
{
	char	*end;
	char	*var_value;
	char	*temp_result;

	end = *start + 1;
	if (*end == '?')
	{
		var_value = ft_itoa(shell_state->last_exit_code);
		end++;
	}
	else if (ft_isalnum(*end) || *end == '_')
		var_value = get_var_value(start, &end, *(shell_state->envp));
	else
	{
		var_value = ft_strdup("$");
		end = *start + 1;
	}
	temp_result = ft_strjoin(prev, var_value);
	free(var_value);
	free(prev);
	if (!temp_result)
		return (NULL);
	*start = end;
	return (temp_result);
}

static char	*find_var(char *end, t_quote_state *q_state)
{
	while (*end != '\0')
	{
		if (q_state->in_quote == FALSE && (*end == '\'' || *end == '\"'))
		{
			q_state->in_quote = TRUE;
			if (*end == '\'')
				q_state->expandable = FALSE;
			q_state->quote_char = *end;
		}
		else if (q_state->in_quote == TRUE && *end == q_state->quote_char)
		{
			q_state->in_quote = FALSE;
			q_state->expandable = TRUE;
			q_state->quote_char = '\0';
		}
		if (q_state->expandable == TRUE && *end == '$')
			break ;
		++end;
	}
	return (end);
}

static char	*handle_plain_text(char **start, char *new_input,
		t_quote_state *q_state)
{
	char	*end;
	char	*plain_text;
	char	*temp_result;

	end = find_var(*start, q_state);
	plain_text = ft_substr(*start, 0, end - *start);
	if (!plain_text)
		return (NULL);
	temp_result = ft_strjoin(new_input, plain_text);
	free(plain_text);
	free(new_input);
	if (!temp_result)
		return (NULL);
	*start = end;
	return (temp_result);
}

char	*env_expander(char *input, t_shell_state *shell_state)
{
	char			*new_input;
	char			*start_ptr;
	t_quote_state	q_state;

	q_state.expandable = TRUE;
	q_state.in_quote = FALSE;
	q_state.quote_char = '\0';
	new_input = ft_strdup("");
	if (new_input == NULL)
		return (NULL);
	start_ptr = input;
	while (*start_ptr)
	{
		if (*start_ptr == '$')
			new_input = handle_var(&start_ptr, new_input, shell_state);
		else
			new_input = handle_plain_text(&start_ptr, new_input, &q_state);
		if (new_input == NULL)
			return (NULL);
	}
	return (new_input);
}
