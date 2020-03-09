#include <unistd.h>
#include "malloc.h"
#include "show_alloc_mem.h"

#define DO_MALLOC 1
#define DO_REALLOC 0
#define DO_FREE 1

#define MALLOC_COUNT 20
#define MALLOC_START_SIZE 1000
#define MALLOC_COEFF 1.5
#define REALLOC_COEFF 0.5

int main()
{
	char *array;
	size_t malloc_size = MALLOC_START_SIZE;
	for (int i = 0; i < MALLOC_COUNT; ++i)
	{
		if (DO_MALLOC)
		{
			array = malloc(malloc_size);
			for (int j = 0; j < malloc_size && array; ++j)
			{
				array[j] = 'A';
			}
			write(1, "--------- AFTER MALLOC ---------\n", 34);
			show_alloc_mem();
		}
		if (DO_REALLOC)
		{
			array = realloc(array, malloc_size * REALLOC_COEFF);
			write(1, "--------- AFTER REALLOC ---------\n", 35);
			show_alloc_mem();
		}
		if (DO_FREE)
		{
			free(array);
			write(1, "--------- AFTER FREE ---------\n", 32);
			show_alloc_mem();
		}
		malloc_size *= MALLOC_COEFF;
	}
	return 0;
}