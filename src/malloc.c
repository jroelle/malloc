#include "malloc.h"

void *malloc(size_t size)
{
	t_chunk *chunk;

	if (!size)
		return (NULL);
	lock_mutex();
	if (!*get_root(TINY))
	{
		pre_allocate();
	}
	size += sizeof(t_chunk);
	chunk = find_freed_chunk(size);
	if (!chunk)
	{
		chunk = create_chunk(size);
	}
	if (!chunk)
	{
		return (NULL);
	}
	else
	{
		set_in_use(chunk);
	}
	unlock_mutex();
	return (get_memory(chunk));
}