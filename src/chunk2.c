/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:10:15 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:10:16 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"

void	add_chunk_to_list(t_chunk *chunk, size_t chunk_size)
{
	t_chunk **root;
	t_chunk *last;

	root = get_root(get_type(chunk_size));
	last = *root;
	while (last && last->next)
	{
		last = last->next;
	}
	chunk->size = chunk_size;
	chunk->prev = last;
	chunk->next = NULL;
	if (last)
	{
		last->next = chunk;
	}
	else
	{
		*root = chunk;
	}
}

void	remove_chunk_from_list(t_chunk *chunk)
{
	if (!chunk)
		return ;
	if (chunk->prev)
		chunk->prev->next = chunk->next;
	if (chunk->next)
		chunk->next->prev = chunk->prev;
}

t_chunk	*create_chunk(size_t size)
{
	t_chunk *chunk;

	chunk = mmap(NULL, size, PROT, FLAGS, -1, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	add_chunk_to_list(chunk, size);
	return (chunk);
}

int		destroy_chunk(t_chunk *chunk)
{
	remove_chunk_from_list(chunk);
	return (munmap(chunk, chunk->size));
}

int		split_chunk(t_chunk *chunk, size_t first_size)
{
	t_chunk *second_chunk;

	if (!chunk || first_size >= chunk->size)
		return (0);
	second_chunk = (t_chunk *)((char *)chunk + first_size);
	add_chunk_to_list(second_chunk, chunk->size - first_size);
	set_free(second_chunk);
	chunk->size = first_size;
	return (1);
}
