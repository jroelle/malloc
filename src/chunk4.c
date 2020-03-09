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

#include "malloc.h"

int		is_in_use(const t_chunk *chunk)
{
	return (chunk->iterations < 0);
}

void	set_in_use(t_chunk *chunk)
{
	chunk->iterations = -1;
}

void	set_free(t_chunk *chunk)
{
	chunk->iterations = 0;
}

t_chunk	*find_prev_free(const t_chunk *chunk)
{
	t_chunk *prev;

	prev = chunk->prev;
	while (prev && is_in_use(prev))
	{
		prev = prev->prev;
	}
	return (prev);
}

t_chunk	*find_next_free(const t_chunk *chunk)
{
	t_chunk *next;

	next = chunk->next;
	while (next && is_in_use(next))
	{
		next = next->next;
	}
	return (next);
}
