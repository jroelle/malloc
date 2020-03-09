/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:35:32 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:35:33 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "show_alloc_mem.h"

char	*get_type_name(t_type type)
{
	if (TINY == type)
		return ("TINY");
	if (SMALL == type)
		return ("SMALL");
	if (LARGE == type)
		return ("LARGE");
	return ("");
}

void	print(const char *str, const char *color)
{
	short	n;
	char	*t;

	if (!str)
		return ;
	if (color)
		write(1, color, COLOR_LENGTH);
	n = 0;
	t = (char *)str;
	while (*(t++))
		++n;
	write(1, str, n);
	if (color)
		write(1, DEFAULT, DEFAULT_LENGTH);
}

void	print_unum(unsigned long n, int base, const char *color)
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

void	print_hex(const void *ptr, const char *color)
{
	intptr_t nptr;

	print("0x", color);
	nptr = (intptr_t)ptr;
	print_unum(nptr, 16, color);
}
