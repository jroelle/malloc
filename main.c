#include <unistd.h>
#include <string.h>
#include "malloc.h"
#include "show_alloc_mem.h"

#define SHOW_MEMORY 1
#define SHOW_MEMORY_CONTENT 0
#define SHOW_INDEX 0

#define DO 1
#define DO_MALLOC 1
#define DO_REALLOC 0
#define DO_FREE 1

#define MALLOC_COUNT 100
#define MALLOC_START_SIZE 1024
#define MALLOC_COEFF 1
#define REALLOC_COEFF 1


int main()
{
#if (DO)
	char *array = NULL;
	size_t malloc_size = MALLOC_START_SIZE;

	for (int i = 0; i < MALLOC_COUNT; ++i)
	{
		if (SHOW_INDEX)
		{
			write(1, "i = ", 5);
			print_unum(i, 10, NULL);
			write(1, "\n", 1);
		}

		if (DO_MALLOC)
		{
			array = malloc(malloc_size);
			memset(array, i % 10 + '0', malloc_size);
			if (SHOW_MEMORY)
			{
				write(1, "--------- AFTER MALLOC ---------\n", 34);
				if (SHOW_MEMORY_CONTENT)
				{
					write(1, array, malloc_size);
					write(1, "\n\n", 2);
				}
				show_alloc_mem();
			}
		}
		if (DO_REALLOC)
		{
			array = realloc(array, malloc_size * REALLOC_COEFF);
			if (SHOW_MEMORY)
			{
				write(1, "--------- AFTER REALLOC ---------\n", 35);
				if (SHOW_MEMORY_CONTENT)
				{
					write(1, array, malloc_size * REALLOC_COEFF);
					write(1, "\n\n", 2);
				}
				show_alloc_mem();
			}
		}
		if (DO_FREE)
		{
			free(array);
			if (SHOW_MEMORY)
			{
				write(1, "--------- AFTER FREE ---------\n", 32);
				show_alloc_mem();
			}
		}
		malloc_size *= MALLOC_COEFF;
	}
	return 0;
#endif
}
