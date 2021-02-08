/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:16:14 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 09:49:22 by user42           ###   ########.fr       */
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
	static t_list	*lights = NULL;

	if (key == ESCAPE)
		exit_prog(rt);
	if (key == TAB)
	{
		if (!cameras || !cameras->next)
			cameras = rt->scene.camera;
		else
			cameras = cameras->next;
		rt->camera = (t_camera *)cameras->content;
		render(rt);
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
	if (key == 'l')
	{
		if (!lights || !lights->next)
			lights = rt->scene.light;
		else
			lights = lights->next;
		rt->light = (t_light *)lights->content;
		rt->transform_focus = LIGHT;
	}
	if (key == 'c')
		rt->transform_focus = CAMERA;
	if (key == 't')
		rt->transform = (rt->transform + 1 == 2 ? TRANSLATE : ROTATE);
	if (key == 'q' || key == 'd' || key == 'z' || key == 's' || key == CONTROL || key == SPACE)
	{
		if (rt->transform_focus == CAMERA)
		{
			rt->transform == TRANSLATE ? move_camera(key, rt->camera->to_world_matrix) : rotate_camera(key, rt->camera);
		}
		else if (rt->transform_focus == OBJECT)
		{
			if (rt->transform == TRANSLATE)
			{
				rt->object->to_world_matrix[3] = move_object(key, rt->object->to_world_matrix[3], rt->camera->to_world_matrix);
				rt->object->position = vector_matrix_mul(new_vector(0, 0, 0), rt->object->to_world_matrix);
			}
			else if (rt->object->direction.x || rt->object->direction.y || rt->object->direction.z)
				rotate_object(key, rt->object, rt->camera);
		}
		else if (rt->transform == TRANSLATE)
			rt->light->position = move_object(key, rt->light->position, rt->camera->to_world_matrix);
		render(rt);
	}
	return (0);
}
