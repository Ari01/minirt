/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:16:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 17:08:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		exit_prog(t_rt *rt)
{
	rt->quit = 1;
	rt->count = 0;
	pthread_cond_broadcast(&rt->add_pixel_cond);
	pthread_cond_wait(&rt->render_cond, &rt->mutex);
	pthread_mutex_unlock(&rt->mutex);
	pthread_exit(NULL);
}

int		key_hook(int key, t_rt *rt)
{
	if (key == ESCAPE)
		exit_prog(rt);
	if (key == 'q' || key == 'd' || key == 'z' || key == 's' || key == CONTROL || key == SPACE)
		camera_move(key, rt);
	return (0);
}
