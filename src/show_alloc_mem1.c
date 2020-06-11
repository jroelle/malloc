/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:11:06 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:11:08 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "show_alloc_mem.h"
#include "mutex.h"

static void	print_chunk(const t_chunk *chunk,
						size_t *total_size, size_t *total_payload_size)
{
	void *memory;

	memory = get_memory(chunk);
	print_hex(memory, NULL);
	print(" - ", NULL);
	print_hex((char *)memory - sizeof(t_chunk) + chunk->size, NULL);
	print("  ", NULL);
	print_hex(chunk, GRAY);
	print(" - ", GRAY);
	print_hex((char *)chunk + chunk->size, GRAY);
	print(is_in_use(chunk) ? " IN USE " : " FREE ",
			is_in_use(chunk) ? RED : GREEN);
	print_unum((int)(chunk->size - sizeof(t_chunk)), 10, NULL);
	print(" (", GRAY);
	print_unum((int)chunk->size, 10, GRAY);
	print(") bytes\n", GRAY);
	*total_size += chunk->size;
	*total_payload_size += chunk->size - sizeof(t_chunk);
}

static void	print_total_size(size_t total_size, size_t total_payload_size)
{
	print("\nTotal : ", YELLOW);
	print_unum(total_payload_size, 10, YELLOW);
	print(" (", GRAY);
	print_unum(total_size, 10, GRAY);
	print(") bytes\n\n", GRAY);
}

static void	print_root(const t_chunk *root, t_type type)
{
	print("\nROOT ", YELLOW);
	print(get_type_name(type), YELLOW);
	print(" : ", YELLOW);
	print_hex(root, YELLOW);
	if (type != LARGE)
	{
		print("\nMAX ", GRAY);
		print_unum(type == TINY ? TINY_COEFF * getpagesize() :
			SMALL_COEFF * getpagesize(), 10, GRAY);
	}
	print("\n", NULL);
}

void		show_alloc_mem(void)
{
	t_type	type;
	t_chunk	*iterator;
	size_t	total_size;
	size_t	total_payload_size;

	lock_mutex();
	total_size = 0;
	total_payload_size = 0;
	type = TINY;
	while (type < TYPE_COUNT)
	{
		iterator = *get_root(type);
		print_root(iterator, type);
		while (iterator)
		{
			print_chunk(iterator, &total_size, &total_payload_size);
			iterator = iterator->next;
		}
		++type;
	}
	print_total_size(total_size, total_payload_size);
	unlock_mutex();
}
