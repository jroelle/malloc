/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:10:10 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:10:12 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"

t_chunk	**get_root(t_type type)
{
	static t_chunk *array[TYPE_COUNT] = { NULL };

	return (&array[type]);
}

t_chunk	*get_chunk(const void *memory)
{
	return ((t_chunk *)((char *)memory - sizeof(t_chunk)));
}

void	*get_memory(const t_chunk *chunk)
{
	return ((char *)chunk + sizeof(t_chunk));
}

t_chunk	*get_free_chunk(size_t chunk_size)
{
	t_chunk	*iterator;
	size_t	split_chunk_size;

	split_chunk_size = chunk_size + sizeof(t_chunk);
	iterator = *get_root(get_type(chunk_size));
	while (iterator)
	{
		if (!is_in_use(iterator) &&
			(chunk_size == iterator->size || iterator->size > split_chunk_size))
		{
			if (iterator->size > split_chunk_size)
				split_chunk(iterator, chunk_size);
			return (iterator);
		}
		iterator = iterator->next;
	}
	return (NULL);
}

t_chunk	*find_chunk(const void *memory)
{
	t_type	type;
	t_chunk	*iterator;

	type = TYPE_FIRST;
	while (type < TYPE_COUNT)
	{
		iterator = *get_root(type);
		while (iterator)
		{
			if (get_memory(iterator) == memory)
				return (iterator);
			iterator = iterator->next;
		}
		++type;
	}
	return (NULL);
}
