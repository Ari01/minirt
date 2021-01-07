/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:10:46 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 18:20:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_thread(t_rt *rt)
{
	int			i;
	int			error;

	rt->thread = malloc(sizeof(*rt->thread) * N_THREAD);
	if (!rt->thread)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < N_THREAD)
	{
		if (!i)
			error = pthread_create(&rt->thread[i], NULL, &render, rt);
		else
			error = pthread_create(&rt->thread[i], NULL, &add_thread_pixel, rt);
		if (error)
		{
			perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < N_THREAD)
	{
		pthread_join(rt->thread[i], NULL);
		i++;
	}
	free(rt->thread);
	free_rt(rt);
}
