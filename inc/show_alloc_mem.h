/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:36:33 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:36:35 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOW_ALLOC_MEM_H
# define SHOW_ALLOC_MEM_H

# include "malloc.h"
# include "chunk.h"

# define STDOUT 1

# define DEF_COLOR			"\x1b[39;49m"
# define YELLOW				"\x1b[33m"
# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define GRAY				"\x1b[90m"

# define DEF_COLOR_LENGTH	9
# define COLOR_LENGTH		6

void		show_alloc_mem(void);
const char	*get_type_name(t_type type);
void		print(const char *str, const char *color);
void		print_unum(unsigned long n, int base, const char *color);
void		print_hex(const void *ptr, const char *color);

#endif
