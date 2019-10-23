#include <stdio.h>
#include "malloc.h"

void show_alloc_mem();

int main()
{
	char *array;
	int n = 1;
	size_t k = 70000;
	int i_not_free = n / 2;
	for (int i = 0; i < n; ++i)
	{
		array = malloc(k);
		for (int j = 0; j < i && array; ++j)
		{
			array[j] = 'A' + j;
		}
		if (i != i_not_free)
		{
			//free(array);
		}
		k /= 2;
	}
	show_alloc_mem();
	return 0;
}