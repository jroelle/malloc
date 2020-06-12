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
	print(")\n\n", GRAY);
	*total_size += chunk->size;
	*total_payload_size += chunk->size - sizeof(t_chunk);
}

static void	print_total_size(size_t total_size, size_t total_payload_size)
{
	print("\nTotal : ", YELLOW);
	print_unum(total_payload_size, 10, YELLOW);
	print(" (", GRAY);
	print_unum(total_size, 10, GRAY);
	print(")\n\n", GRAY);
}

static void	print_type_name(t_type type)
{
	print(get_type_name(type), YELLOW);
	if (LARGE != type)
	{
		print(" (MAX ", GRAY);
		print_unum(TINY == type ? TINY_COEFF * getpagesize() :
			SMALL_COEFF * getpagesize(), 10, GRAY);
		print(")", GRAY);
	}
	print("\n", NULL);
}

static void	print_type_memory(t_type type,
	size_t *total_size, size_t *total_payload_size)
{
	t_chunk	*iterator;
	int		exist;

	print_type_name(type);
	iterator = *get_root();
	exist = 0;
	while (iterator)
	{
		if (get_type(iterator->size) == type)
		{
			print_chunk(iterator, total_size, total_payload_size);
			exist = 1;
		}
		iterator = iterator->next;
	}
	if (!exist)
	{
		print_hex(NULL, NULL);
		print("\n\n", NULL);
	}
}

void		show_alloc_mem(void)
{
	t_type	type;
	size_t	total_size;
	size_t	total_payload_size;

	lock_mutex();
	total_size = 0;
	total_payload_size = 0;
	type = TYPE_FIRST;
	while (type < TYPE_COUNT)
	{
		print_type_memory(type, &total_size, &total_payload_size);
		++type;
	}
	print_total_size(total_size, total_payload_size);
	unlock_mutex();
}
