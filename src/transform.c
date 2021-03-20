/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:28:39 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 08:17:45 by user42           ###   ########.fr       */
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

void		rotate_camera(int key, t_camera *camera)
{
	double		angle;
	t_vector	mtmp[3];

	init_rotation_matrix(mtmp);
	if (key == 'q' || key == 'd')
	{
		angle = (key == 'q' ? -10 : 10);
		set_yrotation_matrix(mtmp, angle);
	}
	if (key == 'z' || key == 's')
	{
		angle = (key == 'z' ? -10 : 10);
		set_xrotation_matrix(mtmp, angle);
	}
	matrix_mul(camera->to_world_matrix, mtmp);
	matrix_cpy(camera->to_cam_matrix, camera->to_world_matrix);
	matrix_invert(camera->to_cam_matrix);
}

t_vector	get_translation(int key, t_vector *cam_matrix)
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
	return (v);
}

void		move_object(t_object *object)
{
	int			i;
	t_vector	tvec;

	tvec = object->to_world_matrix[3];
	i = 0;
	while (i < object->nvertices)
	{
		object->vertex[i] = vector_add(object->vertex[i], tvec);
		i++;
	}
}

void		rotate_object(int key, t_object *object, t_camera *cam)
{
	double		angle;
	t_vector	rotation_matrix[3];
	t_vector	dir;

	if (object->rotate)
	{
		init_rotation_matrix(rotation_matrix);
		if (key == 'q' || key == 'd')
		{
			angle = (key == 'q' ? 90 : -90);
			set_zrotation_matrix(rotation_matrix, angle);
		}
		if (key == 'z' || key == 's')
		{
			angle = (key == 'z' ? 90 : -90);
			set_xrotation_matrix(rotation_matrix, angle);
		}
		matrix_cpy(object->to_world_matrix, cam->to_world_matrix);
		matrix_mul(object->to_world_matrix, rotation_matrix);
		matrix_mul(object->to_world_matrix, cam->to_cam_matrix);
		dir = object->current_direction;
		dir = dir_matrix_mul(dir, object->to_world_matrix);
		dir = vector_normalize(dir);
		object->current_direction = dir;
	}
}
