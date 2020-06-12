/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:10:21 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:10:22 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"

void	merge_chunks(t_chunk *c)
{
	t_chunk *prev;
	t_chunk *next;

	prev = c->prev;
	while (prev && (char *)prev == (char *)c - prev->size && !is_in_use(prev))
	{
		prev->next = c->next;
		if (prev->next)
			prev->next->prev = prev;
		prev->size += c->size;
		prev->iterations = max(prev->iterations, c->iterations);
		c = prev;
		prev = prev->prev;
	}
	next = c->next;
	while (next && (char *)next == (char *)c + c->size && !is_in_use(next))
	{
		c->next = next->next;
		if (c->next)
			c->next->prev = c;
		c->size += next->size;
		c->iterations = max(c->iterations, next->iterations);
		next = next->next;
	}
}

void	update_list(t_chunk *chunk)
{
	if (!chunk)
		return ;
	merge_chunks(chunk);
	update_unused();
}

void	update_unused(void)
{
	t_chunk	*iterator;
	t_chunk	*next;

	iterator = *get_root();
	while (iterator)
	{
		next = iterator->next;
		if (!is_in_use(iterator))
		{
			++(iterator->iterations);
			if (iterator->iterations >= MAX_ITER &&
				iterator->size >= (size_t)getpagesize())
			{
				destroy_chunk(iterator);
			}
		}
		iterator = next;
	}
}

t_type	get_type(size_t chunk_size)
{
	size_t page_size;

	page_size = getpagesize();
	if (chunk_size <= page_size * TINY_COEFF)
		return (TINY);
	if (chunk_size <= page_size * SMALL_COEFF)
		return (SMALL);
	return (LARGE);
}
