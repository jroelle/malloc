/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:10:59 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:11:01 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "chunk.h"
#include "mutex.h"

static void	copy_data(void *dst, const void *src, size_t size)
{
	size_t		i;
	char		*cdst;
	const char	*csrc;

	cdst = (char *)dst;
	csrc = (const char *)src;
	i = 0;
	while (i < size)
	{
		cdst[i] = csrc[i];
		++i;
	}
}

void		*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_chunk	*chunk;

	lock_mutex();
	if (!size)
		return (NULL);
	new_ptr = malloc(size);
	if (!ptr || !new_ptr)
		return (ptr);
	chunk = find_chunk(ptr);
	if (!chunk)
		return (NULL);
	copy_data(new_ptr, ptr, min(size, chunk->size));
	free_chunk(chunk);
	unlock_mutex();
	return (new_ptr);
}
