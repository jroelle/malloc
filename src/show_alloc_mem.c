#include <stdio.h>
#include "malloc.h"

#define DEFAULT "\x1b[39;49m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define GRAY "\x1b[90m"

#define DEFAULT_LENGTH 9
#define COLOR_LENGTH 6

static void print(const char *str, const char *color)
{
	short n;
	char *t;

	if (!str)
		return;
	if (color)
	{
		write(1, color, COLOR_LENGTH);
	}
	n = 0;
	t = (char *)str;
	while (*(t++))
	{
		++n;
	}
	write(1, str, n);
	if (color)
	{
		write(1, DEFAULT, DEFAULT_LENGTH);
	}
}

static void print_unum(unsigned long n, int base, const char *color)
{
	char c;

	if (n >= (unsigned long)base)
		print_unum(n / base, base, color);
	if (n % base < 10)
		c = n % base + '0';
	else
		c = n % base - 10 + 'A';
	print(&c, color);
}

static void print_hex(void *ptr, const char *color)
{
	__intptr_t nptr;

	print("0x", color);
	nptr = (__intptr_t)ptr;
	print_unum(nptr, 16, color);
}

void show_alloc_mem(void)
{
    t_type type;
	t_chunk *iterator;
	size_t total_size;
	size_t total_payload_size;

	total_size = 0;
	total_payload_size = 0;
	type = TINY;
	while (type < TYPE_COUNT)
	{
		iterator = *get_root(type);
		print("\n\t\t\tROOT ", YELLOW);
		print(type == TINY ? "TINY : " : (type == SMALL ? "SMALL : " : "LARGE : "), YELLOW);
		print_hex(iterator, YELLOW);
		if (type != LARGE)
		{
			print("\n\t\t\t\tMAX ", GRAY);
			print_unum(type == TINY ? TINY_COEFF * getpagesize() : SMALL_COEFF * getpagesize(), 10, GRAY);
		}
		print(iterator ? "\n\n\t     MEMORY\t\t\tPAYLOAD/CHUNK\t\tSTATE\n\n" : "\n\t\t\t\t-\n", GRAY);
		while (iterator)
		{
			print_hex(iterator, NULL);
			print(" - ", NULL);
			print_hex(iterator + iterator->size, NULL);
			print("\t\t", NULL);
			print_unum((int)(iterator->size - sizeof(t_chunk)), 10, NULL);
			print("\t", NULL);
			print_unum((int)iterator->size, 10, GRAY);
			print("\t\t", NULL);
			print(is_in_use(iterator) ? " IN USE\n" : " FREED\n", is_in_use(iterator) ? RED : GREEN);
			total_size += iterator->size;
			total_payload_size += iterator->size - sizeof(t_chunk);
			iterator = iterator->next;
		}
		++type;
	}
	print("\n\t\t\t\t\t", NULL);
	print_unum(total_payload_size, 10, YELLOW);
	print("\t", NULL);
	print_unum(total_size, 10, GRAY);
	print("\n\n", NULL);
}