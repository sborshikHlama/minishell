/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:21:30 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/09 21:21:57 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unquote_string(char *str)
{
	int		len;
	char	*result;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '\"' && str[len - 1] == '\"')))
	{
		result = ft_substr(str, 1, len - 2);
		if (!result)
			return (NULL);
		return (result);
	}
	return (ft_strdup(str));
}
