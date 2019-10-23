#include "../inc/malloc.h"

void free(void *ptr)
{
	t_chunk *chunk;

	if (!ptr)
		return;
	lock_mutex();
	chunk = get_chunk(ptr);
	set_free(chunk);
	update_list(chunk);
	unlock_mutex();
}