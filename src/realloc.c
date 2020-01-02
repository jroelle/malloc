#include "malloc.h"

static void copy_data(void *dst, const void *src, size_t size)
{
	size_t i;
	char *cdst;
	const char *csrc;

	cdst = (char *)dst;
	csrc = (const char *)src;
	i = 0;
	while (i < size)
	{
		cdst[i] = csrc[i];
		++i;
	}
}

void *realloc(void *ptr, size_t size)
{
	void *new_ptr;

	lock_mutex();
	if (!size)
		return (NULL);
	new_ptr = malloc(size);
	if (!ptr || !new_ptr)
		return (new_ptr);
	copy_data(new_ptr, ptr, min(size, get_chunk(ptr)->size));
	free(ptr);
	unlock_mutex();
	return (new_ptr);
}