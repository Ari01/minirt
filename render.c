/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 07:10:25 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 18:29:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	img_pixel_put(t_rt *rt, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= rt->width || y < 0 || y >= rt->height)
		return ;
	dst = rt->img.addr + (y * rt->img.line_length + x * (rt->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	add_pixel(t_rt *rt)
{
	int		i;
	int		j;
	t_color	color;

	j = rt->count * rt->height / N_THREAD;
	//rt->camera->position = vector_matrix_mul(rt->camera->position, rt->camera->to_world_matrix);
	while (j < rt->height * (rt->count + 1) / N_THREAD)
	{
		i = 0;
		while (i < rt->width)
		{
			compute_camera(rt, i, j);
			color = trace_ray(rt);
			img_pixel_put(rt, i, j, color_to_trgb(color_clamp(color)));
			i++;
		}
		j++;
	}
}

void	*add_thread_pixel(void *data)
{
	t_rt	*rt;

	rt = (t_rt *)data;
	while (1)
	{

		pthread_mutex_lock(&rt->mutex);
		add_pixel(rt);
		rt->count++;
		if (rt->count == N_THREAD - 1)
			pthread_cond_signal(&rt->render_cond);
		pthread_mutex_unlock(&rt->mutex);
		pthread_cond_wait(&rt->add_pixel_cond, &rt->mutex);
		pthread_mutex_lock(&rt->mutex);
		if (rt->quit)
		{
			rt->count++;
			if (rt->count == N_THREAD - 1)
				pthread_cond_signal(&rt->render_cond);
			pthread_mutex_unlock(&rt->mutex);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&rt->mutex);
	}
	return (NULL);
}

void	*render(void *data)
{
	t_rt	*rt;

	rt = (t_rt *)data;
	pthread_mutex_lock(&rt->mutex);
	pthread_cond_wait(&rt->render_cond, &rt->mutex);
	add_pixel(rt);
	mlx_put_image_to_window(rt->mlx, rt->window, rt->img.img, 0, 0);
	mlx_hook(rt->window, 33, 1L<<0, &exit_prog, rt);
	mlx_hook(rt->window, 2, 1L<<0, &key_hook, rt);
	mlx_loop(rt->mlx);
	return (NULL);
}
