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

const char	*get_type_name(t_type type)
{
	if (TINY == type)
		return ("TINY");
	if (SMALL == type)
		return ("SMALL");
	if (LARGE == type)
		return ("LARGE");
	return ("");
}

void		print(const char *str, const char *color)
{
	short	n;
	char	*t;

	if (!str)
		return ;
	if (color)
		write(STDOUT, color, COLOR_LENGTH);
	n = 0;
	t = (char *)str;
	while (t && *(t++))
		++n;
	write(STDOUT, str, n);
	if (color)
		write(STDOUT, DEF_COLOR, DEF_COLOR_LENGTH);
}

static void	print_char(char c, const char *color)
{
	char str[2];

	str[0] = c;
	str[1] = 0;
	print(str, color);
}

void		print_unum(unsigned long n, int base, const char *color)
{
	char c;

	if (n >= (unsigned long)base)
		print_unum(n / base, base, color);
	if (n % base < 10)
		c = n % base + '0';
	else
		c = n % base - 10 + 'A';
	print_char(c, color);
}

void		print_hex(const void *ptr, const char *color)
{
	print("0x", color);
	print_unum((unsigned long)ptr, 16, color);
}
