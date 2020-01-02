#include "inc/malloc.h"
#include <string.h>
#define ft_memcpy memcpy

void *realloc(void *ptr, size_t size)
{
	void *new_ptr;

	lock_mutex();
	if (!size)
		return (NULL);
	new_ptr = malloc(size);
	if (!ptr || !new_ptr)
		return (new_ptr);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	unlock_mutex();
	return NULL;
}