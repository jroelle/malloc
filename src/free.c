/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:10:34 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:10:36 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	t_chunk *chunk;

	if (!ptr)
		return ;
	lock_mutex();
	chunk = get_chunk(ptr);
	set_free(chunk);
	update_list(chunk);
	unlock_mutex();
}
