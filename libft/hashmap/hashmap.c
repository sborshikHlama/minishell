/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:35:09 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/01 22:17:38 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

unsigned int	hash(const char *key, size_t size)
{
	unsigned long int	value;

	value = 0;
	while (*key != '\0')
	{
		value = value * PRIME_MULTIPLIER + *key;
		key++;
	}
	return (value % size);
}

t_hashmap	*ft_hashmap_create(size_t size)
{
	t_hashmap	*map;
	size_t		i;

	map = malloc(sizeof(t_hashmap));
	if (map == NULL)
		return (NULL);
	map->size = size;
	map->entries = malloc(sizeof(t_hashmap_entry *) * size);
	if (map->entries == NULL)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		map->entries[i] = NULL;
		i++;
	}
	return (map);
}

int	ft_hashmap_insert(t_hashmap *map, const char *key, const char *value)
{
	unsigned int	index;
	t_hashmap_entry	*entry;

	index = hash(key, map->size);
	entry = malloc(sizeof(t_hashmap_entry));
	if (entry == NULL)
		return (-1);
	entry->key = ft_strdup(key);
	entry->value = ft_strdup(value);
	entry->next = map ->entries[index];
	map->entries[index] = entry;
	return (0);
}

char	*ft_hashmap_get(t_hashmap *map, const char *key)
{
	unsigned int	index;
	t_hashmap_entry	*entry;

	index = hash(key, map->size);
	entry = map->entries[index];
	while (entry != NULL)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			return (entry->value);
		}
		entry = entry->next;
	}
	return (NULL);
}

void	ft_hashmap_free(t_hashmap *map)
{
	t_hashmap_entry	*entry;
	t_hashmap_entry	*temp;
	size_t			i;

	i = -1;
	while (++i < map->size)
	{
		entry = map->entries[i];
		while (entry != NULL)
		{
			temp = entry;
			entry = entry-> next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
	}
	free(map->entries);
	free(map);
}
