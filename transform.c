/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:28:39 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 17:29:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	v.x += matrix[3].x;
	v.y += matrix[3].y;
	v.z += matrix[3].z;
	matrix[3] = v;
}

void		rotate_object(int key, t_vector *matrix, t_vector *cam_matrix)
{
	double		xdeg = 0;
	double		ydeg = 0;
	t_vector	mtmp[3];

	(void)cam_matrix;
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

void		rotate_object2(int key, t_rt *rt)
{
	double		angle;
//	t_vector	mtmp[3];
	t_object	*object;
	t_vector	*cam_matrix;
	t_vector	rotation_matrix[3];
	t_vector	world_to_object[3];

	object = rt->object;
	cam_matrix = rt->camera->to_world_matrix;
	if (object->direction.x || object->direction.y || object->direction.z)
	{
		init_rotation_matrix(rotation_matrix);
//		init_rotation_matrix(mtmp);
		printf("b4 dir = %f %f %f\n", object->current_direction.x, object->current_direction.y, object->current_direction.z);
	//	object->direction = dir_matrix_mul(object->direction, cam_matrix);
		if (key == 'q' || key == 'd')
		{
			angle = (key == 'q' ? -10 : 10);
			set_zrotation_matrix(rotation_matrix, angle);
	//		object->direction = dir_matrix_mul(object->direction, mtmp);
		}
		if (key == 'z' || key == 's')
		{
			angle = (key == 'z' ? 10 : -10);
			set_xrotation_matrix(rotation_matrix, angle);
	//		object->direction = dir_matrix_mul(object->direction, mtmp);
		}
		//init_rotation_matrix(object->to_world_matrix);
		//matrix_mul(object->to_world_matrix, cam_matrix);
		//matrix_mul(object->to_world_matrix, rotation_matrix);
	//(void)cam_matrix;
		//object->direction = dir_matrix_mul(object->direction, mtmp);
		//matrix_mul(mtmp, cam_matrix);
		matrix_cpy(world_to_object, cam_matrix);
		matrix_invert(world_to_object);
		//(void)world_to_object;
	//	matrix_cpy(object->to_world_matrix, cam_matrix);
	//	matrix_cpy(object->to_world_matrix, cam_matrix);
		matrix_mul(object->to_world_matrix, cam_matrix);
		matrix_mul(object->to_world_matrix, rotation_matrix);
	//	object->current_direction = dir_matrix_mul(object->current_direction, cam_matrix);
	//	object->current_direction = dir_matrix_mul(object->current_direction, rotation_matrix);

		matrix_mul(object->to_world_matrix, world_to_object);
		object->current_direction = dir_matrix_mul(object->direction, object->to_world_matrix);

		printf("after object to world = %f %f %f\n", object->current_direction.x, object->current_direction.y, object->current_direction.z);
		//object->current_direction = dir_matrix_mul(object->current_direction, world_to_object);
		object->current_direction = vector_mul(1 / vector_len(object->current_direction), object->current_direction);
		render(rt);
		//object->current_direction = dir_matrix_mul(object->current_direction, world_to_object);
	}
}
