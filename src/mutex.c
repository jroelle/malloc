/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:10:53 by jroelle           #+#    #+#             */
/*   Updated: 2020/03/09 16:10:55 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "malloc.h"

static pthread_mutex_t	*get_mutex(void)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	return (&mutex);
}

void					lock_mutex(void)
{
	pthread_mutex_lock(get_mutex());
}

void					unlock_mutex(void)
{
	pthread_mutex_unlock(get_mutex());
}
