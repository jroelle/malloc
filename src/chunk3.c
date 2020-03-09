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

#include "malloc.h"

int		min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

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
		prev->iterations = min(prev->iterations, c->iterations);
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
		c->iterations = min(c->iterations, next->iterations);
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
	t_type	type;

	type = 0;
	while (type < TYPE_COUNT)
	{
		iterator = *get_root(type);
		iterator = iterator ? iterator->next : NULL;
		while (iterator)
		{
			next = iterator->next;
			if (!is_in_use(iterator))
			{
				if (iterator->iterations >= MAX_ITER)
					destroy_chunk(iterator);
				else
					++(iterator->iterations);
			}
			iterator = next;
		}
		++type;
	}
}

t_type	get_type(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	if (size <= page_size * TINY_COEFF)
		return (TINY);
	if (size <= page_size * SMALL_COEFF)
		return (SMALL);
	return (LARGE);
}
