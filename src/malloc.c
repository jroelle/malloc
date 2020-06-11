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

void	*malloc(size_t user_size)
{
	t_chunk	*chunk;
	size_t	chunk_size;

	if (user_size <= 0 || user_size >= (size_t)-1 - sizeof(t_chunk))
		return (NULL);
	lock_mutex();
	chunk_size = user_size + sizeof(t_chunk);
	chunk = get_free_chunk(chunk_size);
	if (!chunk)
		chunk = pre_allocate_and_get_free(chunk_size);
	if (!chunk)
		return (NULL);
	else
		set_in_use(chunk);
	unlock_mutex();
	return (get_memory(chunk));
}
