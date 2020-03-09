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

#include "malloc.h"

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

t_chunk	*get_free_chunk(size_t size)
{
	t_chunk *iterator;

	iterator = *get_root(get_type(size));
	while (iterator)
	{
		if (iterator->size >= size && !is_in_use(iterator))
		{
			if (iterator->size > size)
				split_chunk(iterator, size);
			return (iterator);
		}
		iterator = iterator->next;
	}
	return (NULL);
}

int		pre_allocate(void)
{
	t_chunk	**root;
	size_t	page_size;

	page_size = getpagesize();
	root = get_root(TINY);
	if (!(*root = create_chunk(PRE_ALLOC_TINY_COEFF * page_size)))
		return (0);
	root = get_root(SMALL);
	if (!(*root = create_chunk(PRE_ALLOC_SMALL_COEFF * page_size)))
		return (0);
	return (1);
}
