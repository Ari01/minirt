/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:16:14 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 18:39:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		exit_prog(t_rt *rt)
{
	free_rt(rt);
	exit(EXIT_SUCCESS);
}

int		expose_hook(t_rt *rt)
{
	mlx_put_image_to_window(rt->mlx, rt->window, rt->img.img, 0, 0);
	return (0);
}

t_list	*switch_cam(int key, t_rt *rt, t_list *cameras)
{
	if (key == TAB)
	{
		if (!cameras || !cameras->next)
			cameras = rt->scene.camera;
		else
			cameras = cameras->next;
		rt->camera = (t_camera *)cameras->content;
		render(rt);
	}
	return (cameras);
}

int		key_hook(int key, t_rt *rt)
{
	static t_list	*objects = NULL;
	static t_list	*cameras = NULL;
	static t_list	*lights = NULL;

	if (key == ESCAPE)
		exit_prog(rt);
	cameras = switch_cam(key, rt, cameras);
	grab_focus(key, rt, &objects, &lights);
	transform_hook(key, rt);
	return (0);
}
