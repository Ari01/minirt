/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:16:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/13 16:53:58 by user42           ###   ########.fr       */
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
		printf("cam = %f %f %f\n", rt->camera->position.x, rt->camera->position.y, rt->camera->position.z);

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
	if (key == 'c')
		rt->transform_focus = CAMERA;
	if (key == 't')
		rt->transform = (rt->transform + 1 == 2 ? 0 : 1);
	if (key == 'q' || key == 'd' || key == 'z' || key == 's' || key == CONTROL || key == SPACE)
	{
		if (rt->transform_focus == CAMERA)
			rt->transform == TRANSLATE ? move_camera(key, rt) : rotate_camera(key, rt);
		else
		{
			if (rt->transform == TRANSLATE)
				move_object(key, rt);
			else if (rt->object->rotate)
				rt->object->rotate(key, rt->object);
		}
		render(rt);
	}
	return (0);
}
