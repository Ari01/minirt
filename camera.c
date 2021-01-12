/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:32 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 18:24:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void		move_camera(int key, t_rt *rt)
{
	int move;

	if (rt->camera->direction.z >= 0)
		move = 1;
	else
		move = -1;
	if (key == 'q')
		rt->camera->to_world_matrix[3].x -= move;
	if (key == 'd')
		rt->camera->to_world_matrix[3].x += move;
	if (key == 'z')
		rt->camera->to_world_matrix[3].z += move;
	if (key == 's')
		rt->camera->to_world_matrix[3].z -= move;
	if (key == CONTROL)
		rt->camera->to_world_matrix[3].y += move;
	if (key == SPACE)
		rt->camera->to_world_matrix[3].y -= move;
}

void		rotate_camera(int key, t_rt *rt)
{
	static double	xdeg = 0;
	static double	ydeg = 0;
	double			radx;
	double			rady;

	radx = M_PI / 180;
	rady = M_PI / 180;
	if (key == 'q' || key == 'd')
	{
		xdeg += (key == 'q' ? -10 : 10);
		radx *= xdeg;
		rady *= ydeg;
		rt->camera->to_world_matrix[0].x = cos(radx);
		rt->camera->to_world_matrix[0].z = -sin(radx + rady);
		rt->camera->to_world_matrix[2].x = sin(radx);
		rt->camera->to_world_matrix[2].z = cos(radx + rady);
	}
	if (key == 'z' || key == 's')
	{
		ydeg += (key == 'z' ? -10 : 10);
		rady *= ydeg;
		radx *= xdeg;
		rt->camera->to_world_matrix[1].y = cos(rady);
		rt->camera->to_world_matrix[1].z = sin(radx + rady);
		rt->camera->to_world_matrix[2].y = -sin(rady);
		rt->camera->to_world_matrix[2].z = cos(radx + rady);
	}
}
