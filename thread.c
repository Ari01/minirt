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
	pthread_t	*thread;
	int			i;
	int			error;

	thread = malloc(sizeof(*thread) * N_THREAD);
	if (!thread)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < N_THREAD)
	{
		rt->thread_id = i;
		error = pthread_create(&thread[i], NULL, &render, rt);

	printf("error = %d\n", error);
		if (error)
		{
			perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
		i++;
	}
	printf("yo\n");
	i = 0;
	while (i < N_THREAD)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}
