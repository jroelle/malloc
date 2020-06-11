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

#define PREALLOC_TINY_COEFF 1
#define PREALLOC_SMALL_COEFF 1

size_t	get_preallocate_size(t_type type)
{
	int page_size;

	page_size = getpagesize();
	if (TINY == type)
		return (TINY_COEFF * page_size * PREALLOC_TINY_COEFF);
	else if (SMALL == type)
		return (SMALL_COEFF * page_size * PREALLOC_SMALL_COEFF);
	else
		return (0);
}

t_chunk	*preallocate_and_get_free(size_t chunk_size)
{
	t_type	type;
	t_chunk	*chunk;

	type = get_type(chunk_size);
	if (LARGE == type)
		return (create_chunk(chunk_size));
	else
	{
		chunk = create_chunk(get_preallocate_size(type));
		if (chunk->size > chunk_size + sizeof(t_chunk))
			split_chunk(chunk, chunk_size);
		return (chunk);
	}
}

void	free_chunk(t_chunk *chunk)
{
	if (chunk)
	{
		set_free(chunk);
		update_list(chunk);
	}
}
