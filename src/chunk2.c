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
#include "chunk.h"

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

t_chunk	*create_chunk(size_t chunk_size)
{
	t_chunk *chunk;

	chunk = mmap(NULL, chunk_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (MAP_FAILED == chunk)
		return (NULL);
	add_chunk_to_list(chunk, chunk_size);
	return (chunk);
}

int		destroy_chunk(t_chunk *chunk)
{
	size_t page_size;

	page_size = (size_t)getpagesize();
	if (chunk->size % page_size)
		split_chunk(chunk, chunk->size / page_size * page_size);
	remove_chunk_from_list(chunk);
	return (munmap(chunk, chunk->size));
}

int		split_chunk(t_chunk *chunk, size_t first_chunk_size)
{
	t_chunk	*second_chunk;
	size_t	second_chunk_size;

	if (!chunk || first_chunk_size >= chunk->size)
		return (0);
	second_chunk_size = chunk->size - first_chunk_size;
	if (second_chunk_size > sizeof(t_chunk))
	{
		second_chunk = (t_chunk *)((char *)chunk + first_chunk_size);
		add_chunk_to_list(second_chunk, second_chunk_size);
		set_free(second_chunk);
		chunk->size = first_chunk_size;
		return (1);
	}
	else
	{
		return (0);
	}
}
