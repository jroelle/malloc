#include "inc/malloc.h"

pthread_mutex_t *get_mutex(void)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	return (&mutex);
}

void lock_mutex(void)
{
	pthread_mutex_lock(get_mutex());
}

void unlock_mutex(void)
{
	pthread_mutex_unlock(get_mutex());
}