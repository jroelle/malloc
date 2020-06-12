/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:10:27 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:10:28 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"

#define PREALLOC_TINY_COEFF 128
#define PREALLOC_SMALL_COEFF 128

size_t	get_preallocate_size(size_t chunk_size)
{
	t_type type;
	size_t page_size;

	type = get_type(chunk_size);
	page_size = (size_t)getpagesize();
	if (TINY == type)
		return (page_size * TINY_COEFF * PREALLOC_TINY_COEFF);
	else if (SMALL == type)
		return (page_size * SMALL_COEFF * PREALLOC_SMALL_COEFF);
	else if (chunk_size % page_size)
		return (page_size * (chunk_size / page_size + 1));
	else
		return (chunk_size);
}

t_chunk	*preallocate_and_get_free(size_t chunk_size)
{
	t_chunk	*chunk;

	chunk = create_chunk(get_preallocate_size(chunk_size));
	if (chunk->size > chunk_size + sizeof(t_chunk))
		split_chunk(chunk, chunk_size);
	return (chunk);
}

void	free_chunk(t_chunk *chunk)
{
	if (chunk)
	{
		set_free(chunk);
		update_list(chunk);
	}
}

int		min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int		max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}