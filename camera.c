/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:32 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 16:52:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vector_matrix_mul(t_vector v, t_vector4 *matrix)
{
	v.x = v.x * matrix[0].x + v.y * matrix[1].x + v.z * matrix[2].x + matrix[3].x;
	v.y = v.x * matrix[0].y + v.y * matrix[1].y + v.z * matrix[2].y + matrix[3].y;
	v.z = v.x * matrix[0].z + v.y * matrix[1].z + v.z * matrix[2].z + matrix[3].z;
	return (v);
}

void		compute_camera(t_rt *rt, double x, double y)
{
	double aspect_ratio;
	double scale;
	double max;
	double min;
	t_vector pworld;

	max = MAX(rt->width, rt->height);
	min = MIN(rt->width, rt->height);
	aspect_ratio = max / min;
	scale = tan(M_PI * rt->camera->fov * 0.5 / 180);
	x = ((2 * (x + 0.5) / rt->width) - 1) * scale;
	y = (1 - 2 * (y + 0.5) / rt->height) * scale;
	if (rt->width >= rt->height)
		x *= aspect_ratio;
	else
		y *= aspect_ratio;
	pworld = new_vector(x, y, 1);
	pworld = vector_matrix_mul(pworld, rt->camera->to_world_matrix);
	rt->camera->direction = vector_sub(pworld, rt->camera->position);
	rt->camera->direction = vector_mul(1 / vector_len(rt->camera->direction),
										rt->camera->direction);
}

void		camera_move(int key, t_rt *rt)
{
	if (key == 'q')
	{
		rt->camera->position.x--;
		rt->camera->to_world_matrix[3].x--;
	}
	if (key == 'd')
	{
		rt->camera->position.x++;
		rt->camera->to_world_matrix[3].x++;
	}
	if (key == 'z')
	{
		rt->camera->position.z++;
		rt->camera->to_world_matrix[3].z++;
	}
	if (key == 's')
	{
		rt->camera->position.z--;
		rt->camera->to_world_matrix[3].z--;
	}
	if (key == CONTROL)
	{
		rt->camera->position.y++;
		rt->camera->to_world_matrix[3].y++;
	}
	if (key == SPACE)
	{
		rt->camera->position.y--;
		rt->camera->to_world_matrix[3].y--;
	}
	rt->count = 0;
	pthread_cond_broadcast(&rt->add_pixel_cond);
	pthread_cond_wait(&rt->render_cond, &rt->mutex);
	add_pixel(rt);
	mlx_put_image_to_window(rt->mlx, rt->window, rt->img.img, 0, 0);
	//pthread_mutex_unlock(&rt->mutex);
}
