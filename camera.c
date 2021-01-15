/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:32 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 20:28:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		set_camera_matrix(t_camera *camera)
{
	t_vector right;
	t_vector up;

	/*if (camera->direction.x > 0)
		right = vector_cross(camera->direction, new_vector(0, 1, 0));
	else*/
		right = vector_cross(new_vector(0, 1, 0), camera->direction);
	printf("right = %f %f %f\n", right.x, right.y, right.z);
	up = vector_cross(camera->direction, right);
	printf("up = %f %f %f\n", up.x, up.y, up.z);
	camera->to_world_matrix[0] = right;
	camera->to_world_matrix[1] = up;
	camera->to_world_matrix[2] = camera->direction;
	camera->to_world_matrix[3] = new_vector(camera->position.x,
											camera->position.y,
											camera->position.z);
}

/*
void		set_camera_matrix(t_camera *camera)
{
	t_vector	xm[3];
	t_vector	ym[3];
	t_vector	zm[3];
	double		angle;
	int			i;

	init_rotation_matrix(xm);
	init_rotation_matrix(ym);
	init_rotation_matrix(zm);
	// x
	if (camera->direction.z && camera->direction.y)
		angle = -90 * camera->direction.y + atan(camera->direction.y / camera->direction.z);
	else if (!camera->direction.z && !camera->direction.y)
		angle = 0;
	else if (!camera->direction.z)
		angle = -90 * camera->direction.y;
	else
		angle = 0;
	set_xrotation_matrix(xm, angle);
	// y
	if (camera->direction.z && camera->direction.x)
		angle = 90 * camera->direction.x - atan(camera->direction.x / camera->direction.z);
	else if (!camera->direction.z && !camera->direction.x)
		angle = 0;
	else if (!camera->direction.z)
		angle = 90 * camera->direction.x;
	else
		angle = (camera->direction.z >= 0 ? 0 : 180);
	set_yrotation_matrix(ym, angle);

	matrix_mul(xm, ym);
	i = 0;
	while (i < 4)
	{
		printf("%f %f %f\n", xm[i].x, xm[i].y, xm[i].z);
		i++;
	}
	matrix_mul(xm, zm);
	i = 0;
	while (i < 4)
	{
		printf("%f %f %f\n", xm[i].x, xm[i].y, xm[i].z);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		camera->to_world_matrix[i] = new_vector(xm[i].x, xm[i].y, xm[i].z);
		i++;
	}
	camera->to_world_matrix[3] = new_vector(camera->position.x,
											camera->position.y,
											camera->position.z);
}*/

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
