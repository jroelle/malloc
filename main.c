#include <stdio.h>
#include "malloc.h"

void show_alloc_mem();

int main()
{
	char *array;
	int malloc_count = 20;
	size_t malloc_size = 1000;
	for (int i = 0; i < malloc_count; ++i)
	{
		array = malloc(malloc_size);
		for (int j = 0; j < malloc_size && array; ++j)
		{
			array[j] = 'A';
		}
		show_alloc_mem();
		free(array);
		show_alloc_mem();
		malloc_size *= 1.5;
	}
	return 0;
}