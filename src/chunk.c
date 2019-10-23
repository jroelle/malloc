#include <sys/mman.h>
#include "../inc/malloc.h"

#define MAX_ITER 100
#define PROT (PROT_READ | PROT_WRITE)
#define FLAGS (MAP_PRIVATE | MAP_ANONYMOUS)
#define PRE_ALLOC_TINY_COEFF TINY_COEFF
#define PRE_ALLOC_SMALL_COEFF SMALL_COEFF

t_chunk **get_root(t_type type)
{
	static t_chunk *array[TYPE_COUNT] = {NULL};
	return (&array[type]);
}

t_chunk *get_chunk(void *memory)
{
	return ((t_chunk *)((char *)memory - sizeof(t_chunk)));
}

void *get_memory(t_chunk *chunk)
{
	return ((char *)chunk + sizeof(t_chunk));
}

t_chunk *find_freed_chunk(size_t size)
{
	t_chunk *iterator;

	iterator = *get_root(get_type(size));
	while (iterator)
	{
		if (iterator->size > size && !is_in_use(iterator))
		{
			split_chunk(iterator, size);
			return (iterator);
		}
		iterator = iterator->next;
	}
	return (NULL);
}

void merge_chunks(t_chunk *chunk)
{
	t_chunk *prev;
	t_chunk *next;

	if (!chunk)
		return;
	prev = chunk->prev;
	next = chunk->next;
	if (prev && prev + prev->size == chunk && !is_in_use(prev))
	{
		prev->next = chunk->next;
		chunk->prev = prev->prev;
		chunk->size += prev->size;
	}
	if (next && next - next->size == chunk && !is_in_use(next))
	{
		next->prev = chunk->prev;
		chunk->next = next->next;
		chunk->size += next->size;
	}
}

void add_chunk_to_list(t_chunk *chunk, size_t chunk_size)
{
	t_chunk **root;

	root = get_root(get_type(chunk_size));
	chunk->size = chunk_size;
	chunk->prev = NULL;
	chunk->next = *root;
	if (*root)
	{
		(*root)->prev = chunk;
	}
	*root = chunk;
}

void remove_chunk_from_list(t_chunk *chunk)
{
	if (!chunk)
		return;
	if (chunk->prev)
		chunk->prev->next = chunk->next;
	if (chunk->next)
		chunk->next->prev = chunk->prev;
}

t_chunk *create_chunk(size_t size)
{
	t_chunk *chunk;
	
	chunk = mmap(NULL, size, PROT, FLAGS, -1, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	add_chunk_to_list(chunk, size);
	return (chunk);
}

int destroy_chunk(t_chunk *chunk)
{
	remove_chunk_from_list(chunk);
	return (munmap(chunk, chunk->size));
}

int split_chunk(t_chunk *chunk, size_t first_size)
{
	t_chunk *second_chunk;

	if (!chunk || first_size >= chunk->size)
		return (0);
	second_chunk = (t_chunk *)((char *)chunk + first_size);
	add_chunk_to_list(second_chunk, chunk->size - first_size);
	set_free(second_chunk);
	chunk->size = first_size;
	return (1);
}

int is_in_use(t_chunk *chunk)
{
	return (chunk->iterations < 0);
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
		while (iterator)
		{
			next = iterator->next;
			if (!is_in_use(iterator) && iterator->iterations >= MAX_ITER)
			{
				destroy_chunk(iterator);
			}
			else
			{
				++iterator->iterations;
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

void set_in_use(t_chunk *chunk)
{
	chunk->iterations = -1;
}

void set_free(t_chunk *chunk)
{
	chunk->iterations = 0;
}

t_chunk *find_prev_free(t_chunk *chunk)
{
	t_chunk *prev;

	prev = chunk->prev;
	while (prev && is_in_use(prev))
	{
		prev = prev->prev;
	}
	return (prev);
}

t_chunk *find_next_free(t_chunk *chunk)
{
	t_chunk *next;
	next = chunk->next;
	while (next && is_in_use(next))
	{
		next = next->next;
	}
	return (next);
}

void pre_allocate(void)
{
	t_chunk **root;
	size_t page_size;

	page_size = getpagesize();
	root = get_root(TINY);
	*root = create_chunk(PRE_ALLOC_TINY_COEFF * page_size);

	root = get_root(SMALL);
	*root = create_chunk(PRE_ALLOC_SMALL_COEFF * page_size);
}