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

#include "chunk.h"

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
