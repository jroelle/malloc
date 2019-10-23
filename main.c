#include <stdio.h>
#include "malloc.h"

void show_alloc_mem();

int main()
{
	char *array;
	int n = 2;
	int k = 1000;
	for (int i = 0; i < 2; ++i)
	{
		array = malloc(k);
		for (int j = 0; j < i && array; ++j)
		{
			array[j] = 'A' + j;
		}
		// if (i % 2)
		// 	free(array);
		k *= 2;
	}
	show_alloc_mem();
	return 0;
}