/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:16:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 17:16:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		exit_prog(t_rt *rt)
{
	free_rt(rt);
	exit(EXIT_SUCCESS);
}

int		key_hook(int key, t_rt *rt)
{
	static t_list	*objects = NULL;
	static t_list	*cameras = NULL;

	if (key == ESCAPE)
		exit_prog(rt);
	if (key == TAB)
	{
		if (!cameras || !cameras->next)
			cameras = rt->scene.camera;
		else
			cameras = cameras->next;
		rt->camera = (t_camera *)cameras->content;
		//set_object_matrix(rt->scene.objects, rt->camera->to_world_matrix);
		render(rt);
		printf("cam = %f %f %f \n %f %f %f \n %f %f %f \n", rt->camera->to_world_matrix[0].x, rt->camera->to_world_matrix[0].y, rt->camera->to_world_matrix[0].z, rt->camera->to_world_matrix[1].x, rt->camera->to_world_matrix[1].y, rt->camera->to_world_matrix[1].z, rt->camera->to_world_matrix[2].x, rt->camera->to_world_matrix[2].y, rt->camera->to_world_matrix[2].z);
	}
	if (key == 'o')
	{
		if (!objects || !objects->next)
			objects = rt->scene.objects;
		else
			objects = objects->next;
		rt->object = (t_object *)objects->content;
		rt->transform_focus = OBJECT;
	}
	if (key == 'c')
		rt->transform_focus = CAMERA;
	if (key == 't')
		rt->transform = (rt->transform + 1 == 2 ? 0 : 1);
	if (key == 'q' || key == 'd' || key == 'z' || key == 's' || key == CONTROL || key == SPACE)
	{
		if (rt->transform_focus == CAMERA)
		{
			rt->transform == TRANSLATE ? move_object(key, rt->camera->to_world_matrix, rt->camera->to_world_matrix) : rotate_object(key, rt->camera->to_world_matrix, rt->camera->to_world_matrix);
			render(rt);
		}
		else
		{
			if (rt->transform == TRANSLATE)
			{
				move_object(key, rt->object->to_world_matrix, rt->camera->to_world_matrix);
				rt->object->position = vector_matrix_mul(new_vector(0, 0, 0), rt->object->to_world_matrix);
				render(rt);
			}
			else if (rt->object->direction.x || rt->object->direction.y || rt->object->direction.z)
			{
				//rotate_object2(key, rt->object, rt->camera->to_world_matrix);
				rotate_object2(key, rt);
		//		render(rt);
		//		t_vector world_to_object[3];
		//		matrix_cpy(world_to_object, rt->camera->to_world_matrix);
		//		matrix_invert(world_to_object);
		//		rt->object->current_direction = dir_matrix_mul(rt->object->current_direction, world_to_object);
				//rt->object->direction = vector_matrix_mul(rt->object->direction, rt->object->to_world_matrix);
			}
		}
	//	render(rt);
	}
	return (0);
}
