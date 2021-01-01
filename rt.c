/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:34:58 by user42            #+#    #+#             */
/*   Updated: 2021/01/01 19:05:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rt	init_rt()
{
	t_rt rt;

	rt.width = -1;
	rt.height = -1;
	rt.scene = init_scene();
	return (rt);
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
}
