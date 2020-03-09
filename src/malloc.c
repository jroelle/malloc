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

void	*malloc(size_t size)
{
	t_chunk *chunk;

	if (size <= 0 || size >= (size_t)-1 - sizeof(t_chunk))
		return (NULL);
	lock_mutex();
	if (!*get_root(TINY) && !pre_allocate())
		return (NULL);
	size += sizeof(t_chunk);
	chunk = get_free_chunk(size);
	if (!chunk)
		chunk = create_chunk(size);
	if (!chunk)
		return (NULL);
	else
		set_in_use(chunk);
	unlock_mutex();
	return (get_memory(chunk));
}
