/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:17:08 by aevstign          #+#    #+#             */
/*   Updated: 2023/10/25 15:06:51 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_str(char	**strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	count_words(const char	*str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			word++;
		i++;
	}
	return (word);
}

static int	get_word_length(const char *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start + len] && s[start + len] != c)
		len++;
	return (len);
}

static char	*allocate_and_copy_word(const char *s, char c, int start)
{
	int		len;
	char	*word;

	len = get_word_length(s, c, start);
	word = (char *)malloc(len + 1);
	if (word)
	{
		ft_strlcpy(word, s + start, len + 1);
		word[len] = '\0';
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	i = 0;
	j = 0;
	while (i < count_words(s, c))
	{
		if (s[j] && s[j] != c)
		{
			result[i++] = allocate_and_copy_word(s, c, j);
			if (!result[i - 1])
			{
				free_str(result);
				return (NULL);
			}
			j += get_word_length(s, c, j);
		}
		else
			j++;
	}
	result[count_words(s, c)] = NULL;
	return (result);
}

// int main() {
//     char *s = "hello_world_this_is_a_test";
//     char **words = ft_split(s, '_');

//     if (words) {
//         for (int i = 0; words[i]; i++) {
//             printf("%s\n", words[i]);
//         }
//         free_str(words);  // Free each string and the array itself
//     }

//     return 0;
// }