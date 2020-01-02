#include "malloc.h"

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

void merge_chunks(t_chunk *chunk)
{
	t_chunk *prev;
	t_chunk *next;

	if (!chunk)
		return;
	prev = chunk->prev;
	while (prev && (char *)prev == (char *)chunk - prev->size && !is_in_use(prev))
	{
		prev->next = chunk->next;
		if (prev->next)
			prev->next->prev = prev;
		prev->size += chunk->size;
		prev->iterations = min(prev->iterations, chunk->iterations);
		chunk = prev;
		prev = prev->prev;
	}
	next = chunk->next;
	while (next && (char *)next == (char *)chunk + chunk->size && !is_in_use(next))
	{
		chunk->next = next->next;
		if (chunk->next)
			chunk->next->prev = chunk;
		chunk->size += next->size;
		chunk->iterations = min(chunk->iterations, next->iterations);
		next = next->next;
	}
}

void update_list(t_chunk *chunk)
{
	merge_chunks(chunk);
	update_unused();
}

void update_unused(void)
{
	t_chunk *iterator;
	t_chunk *next;
	t_type type;

	type = 0;
	while (type < TYPE_COUNT)
	{
		iterator = *get_root(type);
		iterator = iterator ? iterator->next : NULL;
		while (iterator)
		{
			next = iterator->next;
			if (!is_in_use(iterator))
			{
				if (iterator->iterations >= MAX_ITER)
					destroy_chunk(iterator);
				else
					++(iterator->iterations);					
			}
			iterator = next;		
		}
		++type;
	}
}

t_type get_type(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	if (size <= page_size * TINY_COEFF)
		return TINY;
	if (size <= page_size * SMALL_COEFF)
		return SMALL;
	return LARGE;
}