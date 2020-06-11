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

#define PRE_ALLOC_TINY_COEFF TINY_COEFF
#define PRE_ALLOC_SMALL_COEFF SMALL_COEFF

size_t	get_pre_allocate_size(t_type type)
{
	int page_size;

	page_size = getpagesize();
	if (TINY == type)
		return (PRE_ALLOC_TINY_COEFF * page_size);
	else if (SMALL == type)
		return (PRE_ALLOC_SMALL_COEFF * page_size);
	else
		return (0);
}

t_chunk	*pre_allocate_and_get_free(size_t chunk_size)
{
	t_type	type;
	t_chunk	*chunk;

	type = get_type(chunk_size);
	if (LARGE == type)
		return (create_chunk(chunk_size));
	else
	{
		chunk = create_chunk(get_pre_allocate_size(type));
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
