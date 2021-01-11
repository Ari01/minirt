/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:34:58 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 16:01:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rt	init_rt()
{
	t_rt rt;

	rt.width = -1;
	rt.height = -1;
	rt.scene = init_scene();
	rt.transform = TRANSLATE;
	rt.transform_focus = CAMERA;
	rt.scene.camera = NULL;
	rt.scene.light = NULL;
	rt.scene.objects = NULL;
	return (rt);
}

void	free_object(void *object)
{
	t_object *tmp;

	tmp = (t_object *)object;
	if (tmp)
	{
		if (tmp->ptr)
			free(tmp->ptr);
		free(tmp);
	}
}

void	free_rt(t_rt *rt)
{
	ft_lstclear(&rt->scene.camera, &free);
	ft_lstclear(&rt->scene.light, &free);
	ft_lstclear(&rt->scene.objects, &free_object);
	mlx_destroy_image(rt->mlx, rt->img.img);
	mlx_clear_window(rt->mlx, rt->window);
	mlx_destroy_window(rt->mlx, rt->window);
	mlx_destroy_display(rt->mlx);
	free(rt->mlx);
}

void	set_mlx(t_rt *rt)
{
	int width;
	int height;

	rt->mlx = mlx_init();
	mlx_get_screen_size(rt->mlx, &width, &height);
	rt->width = MIN(rt->width, width);
	rt->height = MIN(rt->height, height);
	rt->window = mlx_new_window(rt->mlx, rt->width, rt->height, "minirt");
	rt->img.img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->img.addr = mlx_get_data_addr(rt->img.img,
										&rt->img.bits_per_pixel,
										&rt->img.line_length,
										&rt->img.endian);
	printf("w = %f, h = %f\n", rt->width, rt->height);
}
