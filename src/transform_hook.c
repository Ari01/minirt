/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:35:20 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 18:35:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	transform_cam(int key, t_rt *rt)
{
	if (rt->transform == TRANSLATE)
		move_camera(key, rt->camera->to_world_matrix);
	else
		rotate_camera(key, rt->camera);
}

void	transform_object(int key, t_rt *rt)
{
	t_vector	translation;

	if (rt->transform == TRANSLATE)
	{
		translation = get_translation(key, rt->camera->to_world_matrix);
		rt->object->to_world_matrix[3] = translation;
		move_object(rt->object);
	}
	else if (rt->object->rotate)
		rotate_object(key, rt->object, rt->camera);
}

void	transform_hook(int key, t_rt *rt)
{
	t_vector	translation;

	if (key == 't')
		rt->transform = (rt->transform + 1 == 2 ? TRANSLATE : ROTATE);
	if (key == 'q' || key == 'd' || key == 'z'
		|| key == 's' || key == CONTROL || key == SPACE)
	{
		if (rt->transform_focus == CAMERA)
			transform_cam(key, rt);
		else if (rt->transform_focus == OBJECT)
			transform_object(key, rt);
		else if (rt->transform == TRANSLATE)
		{
			translation = get_translation(key, rt->camera->to_world_matrix);
			rt->light->position = vector_add(rt->light->position, translation);
		}
		render(rt);
	}
}
