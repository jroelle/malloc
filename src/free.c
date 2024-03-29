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
#include "chunk.h"
#include "mutex.h"

void	free(void *ptr)
{
	if (!ptr)
		return ;
	lock_mutex();
	free_chunk(find_chunk(ptr));
	unlock_mutex();
}
