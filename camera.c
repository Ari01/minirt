/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:32 by user42            #+#    #+#             */
/*   Updated: 2021/01/13 21:50:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_rotation_matrix(t_vector *m)
{
	m[0] = new_vector(1, 0, 0);
	m[1] = new_vector(0, 1, 0);
	m[2] = new_vector(0, 0, 1);
}

void		set_xrotation_matrix(t_vector *m, double angle)
{
	angle *= M_PI / 180;
	m[1].y = cos(angle);
	m[1].z = sin(angle);
	m[2].y = -sin(angle);
	m[2].z = cos(angle);
}

void		set_yrotation_matrix(t_vector *m, double angle)
{
	angle *= M_PI / 180;
	m[0].x = cos(angle);
	m[0].z = -sin(angle);
	m[2].x = sin(angle);
	m[2].z = cos(angle);
}

void		set_zrotation_matrix(t_vector *m, double angle)
{
	angle *= M_PI / 180;
	m[0].x = cos(angle);
	m[0].y = sin(angle);
	m[1].x = -sin(angle);
	m[1].y = cos(angle);
}

void		set_camera_matrix(t_camera *camera)
{
	t_vector	xm[3];
	t_vector	ym[3];
	t_vector	zm[3];
	int			i;

	init_rotation_matrix(xm);
	init_rotation_matrix(ym);
	init_rotation_matrix(zm);
	set_xrotation_matrix(xm, (camera->direction.y + camera->direction.z) / 2 * 90);
	set_yrotation_matrix(ym, (camera->direction.x + camera->direction.z) / 2 * 90);
	set_zrotation_matrix(zm, camera->direction.z * 90);
	i = 0;
	while (i < 4)
	{
		printf("%f %f %f\n", xm[i].x, xm[i].y, xm[i].z);
		i++;
	}
	matrix_mul(xm, ym);
	i = 0;
	while (i < 4)
	{
		printf("%f %f %f\n", xm[i].x, xm[i].y, xm[i].z);
		i++;
	}
	/*matrix_mul(xm, zm);
	i = 0;
	while (i < 4)
	{
		printf("%f %f %f\n", xm[i].x, xm[i].y, xm[i].z);
		i++;
	}*/
	i = 0;
	while (i < 3)
	{
		camera->to_world_matrix[i] = new_vector(xm[i].x, xm[i].y, xm[i].z);
		i++;
	}
	camera->to_world_matrix[3] = new_vector(camera->position.x,
											camera->position.y,
											camera->position.z);
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
	if (key == SPACE)
		rt->camera->to_world_matrix[3].y += move;
	if (key == CONTROL)
		rt->camera->to_world_matrix[3].y -= move;
}

void		rotate_camera(int key, t_rt *rt)
{
	static double	xdeg = 0;
	static double	ydeg = 0;

	if (key == 'q' || key == 'd')
	{
		xdeg += (key == 'q' ? -10 : 10);
		set_yrotation_matrix(rt->camera->to_world_matrix, xdeg);
	}
	if (key == 'z' || key == 's')
	{
		ydeg += (key == 'z' ? -10 : 10);
		set_xrotation_matrix(rt->camera->to_world_matrix, ydeg);
	}
}
