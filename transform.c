/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:28:39 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 18:55:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		move_camera(int key, t_vector *matrix)
{
	t_vector	v;

	if (key == 'q')
		v = new_vector(-1, 0, 0);
	if (key == 'd')
		v = new_vector(1, 0, 0);
	if (key == 'z')
		v = new_vector(0, 0, 1);
	if (key == 's')
		v = new_vector(0, 0, -1);
	if (key == SPACE)
		v = new_vector(0, 1, 0);
	if (key == CONTROL)
		v = new_vector(0, -1, 0);
	v = dir_matrix_mul(v, matrix);
	matrix[3] = vector_add(matrix[3], v);
}

void		rotate_camera(int key, t_vector *matrix)
{
	double		xdeg = 0;
	double		ydeg = 0;
	t_vector	mtmp[3];

	init_rotation_matrix(mtmp);
	if (key == 'q' || key == 'd')
	{
		xdeg += (key == 'q' ? -10 : 10);
		set_yrotation_matrix(mtmp, xdeg);
		matrix_mul(matrix, mtmp);
	}
	if (key == 'z' || key == 's')
	{
		ydeg += (key == 'z' ? 10 : -10);
		set_xrotation_matrix(mtmp, ydeg);
		matrix_mul(matrix, mtmp);
	}
}

void		move_object(int key, t_vector *matrix, t_vector *cam_matrix)
{
	t_vector	v;

	if (key == 'q')
		v = new_vector(-1, 0, 0);
	if (key == 'd')
		v = new_vector(1, 0, 0);
	if (key == 'z')
		v = new_vector(0, 0, 1);
	if (key == 's')
		v = new_vector(0, 0, -1);
	if (key == SPACE)
		v = new_vector(0, 1, 0);
	if (key == CONTROL)
		v = new_vector(0, -1, 0);
	v = dir_matrix_mul(v, cam_matrix);
	matrix[3] = vector_add(matrix[3], v);
}

void		rotate_object(int key, t_object *object, t_camera *cam)
{
	double		angle;
	t_vector	rotation_matrix[3];

	if (object->rotate)
	{
		init_rotation_matrix(rotation_matrix);
		angle = 1;
		if (!vector_dot(object->direction, new_vector(0, 1, 0)))
			angle *= -1;
		if (key == 'q' || key == 'd')
		{	
			angle *= (key == 'q' ? -40 : 40);
			set_zrotation_matrix(rotation_matrix, angle);
		}
		if (key == 'z' || key == 's')
		{
			angle *= (key == 'z' ? 40 : -40);
			set_xrotation_matrix(rotation_matrix, angle);
		}
		matrix_mul(object->to_world_matrix, cam->to_world_matrix);
		matrix_mul(object->to_world_matrix, rotation_matrix);
		matrix_mul(object->to_world_matrix, cam->to_cam_matrix);
		object->current_direction = dir_matrix_mul(object->direction, object->to_world_matrix);
		object->current_direction = vector_mul(1 / vector_len(object->current_direction), object->current_direction);
	}
}
