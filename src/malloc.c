/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:10:45 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:10:47 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "chunk.h"
#include "mutex.h"

void	*do_malloc(size_t user_size)
{
	t_chunk	*chunk;
	size_t	chunk_size;

	if (!user_size)
		return (NULL);
	chunk_size = user_size + sizeof(t_chunk);
	chunk = get_free_chunk(chunk_size);
	if (!chunk)
		chunk = pre_allocate_and_get_free(chunk_size);
	if (!chunk)
		return (NULL);
	else
		set_in_use(chunk);
	return (get_memory(chunk));
}

void	*malloc(size_t user_size)
{
	void *memory;

	lock_mutex();
	memory = do_malloc(user_size);
	unlock_mutex();
	return (memory);
}
