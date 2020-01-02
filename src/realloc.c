#include "inc/malloc.h"

void *realloc(void *ptr, size_t size)
{
	lock_mutex();
	if (!ptr)
		return (malloc(size));
	unlock_mutex();
	return NULL;
}