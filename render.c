/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 07:10:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 09:47:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	img_pixel_put(t_rt *rt, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= rt->width || y < 0 || y >= rt->height)
		return ;
	dst = rt->img.addr + (y * rt->img.line_length + x * (rt->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render(t_rt *rt)
{
	int		i;
	int		j;
	t_color	color;

	j = 0;
	rt->camera->position = vector_matrix_mul(new_vector(0, 0, 0), rt->camera->to_world_matrix);
	while (j < rt->height)
	{
		i = 0;
		while (i < rt->width)
		{
			compute_camera(rt, i, j);
			rt->ray = new_ray(rt->camera->position, rt->camera->direction);
			color = trace_ray(rt, 0);
			img_pixel_put(rt, i, j, color_to_trgb(color_clamp(color)));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(rt->mlx, rt->window, rt->img.img, 0, 0);
}
