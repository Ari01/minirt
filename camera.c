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

t_vector	vector_matrix_mul(t_vector v, t_vector *matrix)
{
	v.x = v.x * matrix[0].x + v.y * matrix[1].x + v.z * matrix[2].x + matrix[3].x;
	v.y = v.x * matrix[0].y + v.y * matrix[1].y + v.z * matrix[2].y + matrix[3].y;
	v.z = v.x * matrix[0].z + v.y * matrix[1].z + v.z * matrix[2].z + matrix[3].z;
	return (v);
}

void		matrix_mul(t_vector *m1, t_vector *m2)
{
	int			i;
	t_vector	mul[3];

	i = 0;
	while (i < 3)
	{
		mul[i].x = m1[0].x * m2[i].x + m1[1].x * m2[i].y + m1[2].x * m2[i].z;
		mul[i].y = m1[0].y * m2[i].x + m1[1].y * m2[i].y + m1[2].y * m2[i].z;
		mul[i].z = m1[0].z * m2[i].x + m1[1].z * m2[i].y + m1[2].z * m2[i].z;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		m1[i] = new_vector(mul[i].x, mul[i].y, mul[i].z);
		i++;
	}
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

void		init_rotation_matrix(t_vector *matrix)
{
	matrix[0] = new_vector(1, 0, 0);
	matrix[1] = new_vector(0, 1, 0);
	matrix[2] = new_vector(0, 0, 1);
}

void		move_camera(int key, t_rt *rt)
{
	//reset_rotation_matrix(rt);
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
}

void		rotate_camera(int key, t_rt *rt)
{
	double		deg;
	t_vector	matrix[3];

	matrix[0] = new_vector(1, 0, 0);
	matrix[1] = new_vector(0, 1, 0);
	matrix[2] = new_vector(0, 0, 1);
	//init_rotation_matrix(matrix);
	//rt->camera->to_world_matrix[3] = new_vector(0,0,0);
	if (key == 'q' || key == 'd')
	{
		deg = (key == 'q' ? -10 : 10) * M_PI / 180;
		printf("deg = %f\n", deg);
		matrix[0].x = cos(deg);
		matrix[0].z = -sin(deg);
		matrix[2].x = sin(deg);
		matrix[2].z = cos(deg);
		printf("m0.x b4 = %f\n", rt->camera->to_world_matrix[0].x);
		matrix_mul(rt->camera->to_world_matrix, matrix);
		printf("m0.x after = %f\n", rt->camera->to_world_matrix[0].x);
	}
	if (key == 'z' || key == 's')
	{
		deg = (key == 'z' ? -10 : 10) * M_PI / 180;
		matrix[1].y = cos(deg);
		matrix[1].z = sin(deg);
		matrix[2].y = -sin(deg);
		matrix[2].z = cos(deg);
		matrix_mul(rt->camera->to_world_matrix, matrix); 
	}
}
