/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:08:57 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:09:10 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

# define TINY_COEFF 1
# define SMALL_COEFF 16

# define MAX_ITER 100
# define PROT (PROT_READ | PROT_WRITE)
# define FLAGS (MAP_PRIVATE | MAP_ANONYMOUS)
# define PRE_ALLOC_TINY_COEFF TINY_COEFF
# define PRE_ALLOC_SMALL_COEFF SMALL_COEFF

typedef struct	s_chunk
{
	size_t			size;
	struct s_chunk	*prev;
	struct s_chunk	*next;
	int				iterations;
}				t_chunk;

typedef enum	e_type
{
	TINY,
	SMALL,
	LARGE,

	TYPE_COUNT
}				t_type;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

t_chunk			**get_root(t_type type);
t_chunk			*get_chunk(const void *memory);
void			*get_memory(const t_chunk *chunk);
t_chunk			*get_free_chunk(size_t size);
void			merge_chunks(t_chunk *chunk);
void			add_chunk_to_list(t_chunk *chunk, size_t chunk_size);
void			remove_chunk_from_list(t_chunk *chunk);
t_chunk			*create_chunk(size_t size);
int				destroy_chunk(t_chunk *chunk);
int				split_chunk(t_chunk *chunk, size_t first_size);
int				is_in_use(const t_chunk *chunk);
void			update_list(t_chunk *chunk);
void			update_unused(void);
t_type			get_type(size_t size);
void			set_in_use(t_chunk *chunk);
void			set_free(t_chunk *chunk);
t_chunk			*find_prev_free(const t_chunk *chunk);
t_chunk			*find_next_free(const t_chunk *chunk);
int				pre_allocate(void);
int				min(int a, int b);

void			lock_mutex(void);
void			unlock_mutex(void);

#endif
