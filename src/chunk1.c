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

t_chunk	**get_root(void)
{
	static t_chunk *root = NULL;

	return (&root);
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
	iterator = *get_root();
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
	t_chunk	*iterator;

	iterator = *get_root();
	while (iterator)
	{
		if (get_memory(iterator) == memory)
			return (iterator);
		iterator = iterator->next;
	}
	return (NULL);
}
