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

#ifndef CHUNK_H
# define CHUNK_H

# include <unistd.h>

# define TINY_COEFF 2
# define SMALL_COEFF 16

# define MAX_ITER 4096

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

	TYPE_COUNT,

	TYPE_FIRST = TINY,
	TYPE_LAST = LARGE
}				t_type;

t_chunk			**get_root(t_type type);
t_chunk			*get_chunk(const void *memory);
void			*get_memory(const t_chunk *chunk);
t_chunk			*get_free_chunk(size_t chunk_size);
void			merge_chunks(t_chunk *chunk);
void			add_chunk_to_list(t_chunk *chunk, size_t chunk_size);
void			remove_chunk_from_list(t_chunk *chunk);
t_chunk			*create_chunk(size_t chunk_size);
int				destroy_chunk(t_chunk *chunk);
int				split_chunk(t_chunk *chunk, size_t first_chunk_size);
int				is_in_use(const t_chunk *chunk);
void			update_list(t_chunk *chunk);
void			update_unused(void);
t_type			get_type(size_t chunk_size);
void			set_in_use(t_chunk *chunk);
void			set_free(t_chunk *chunk);
int				min(int a, int b);
size_t			get_preallocate_size(t_type type);
t_chunk			*preallocate_and_get_free(size_t chunk_size);
t_chunk			*find_chunk(const void *memory);
void			free_chunk(t_chunk *chunk);
void			*do_malloc(size_t user_size);

#endif
