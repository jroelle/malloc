#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
	lock_mutex();
	unlock_mutex();
}