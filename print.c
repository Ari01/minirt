/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:18:43 by user42            #+#    #+#             */
/*   Updated: 2020/12/14 17:06:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		add_pixel_color(t_rt *rt, t_holder *holder, void *current_object, double intersection)
{
	t_vector	normal;
	t_vector	new_start;
	t_vector	scaled;
	int			x;
	int			y;

	x = holder->camera->viewray.start.x;
	y = holder->camera->viewray.start.y;
	if (current_object != NULL)
	{
		scaled = vectorScale(intersection, holder->camera->viewray.dir);
		new_start = vectorAdd(holder->camera->viewray.start, scaled);
		if (get_normal(&normal, new_start, ((t_sphere *)current_object)->pos))
		{
			img_pixel_put(rt, x, y, 
			color_to_trgb(get_light_value(holder, *(t_sphere *)current_object, new_start, normal)));
		}
	}
}
/*
void		print_object(t_rt *rt, t_holder *holder)
{
	double	intersection;
	t_vector normal;
	t_vector new_start;
	t_vector scaled;
	t_color	color;
	int x,y;

	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			color = new_color(0, 0, 0);
			holder->camera->viewray.start = new_vector(x, y, -2000);
			holder->camera->viewray.dir = new_vector(0, 0, 1);

			int i;
			int current_sphere;

			intersection = 20000.0f;
			i = 0;
			current_sphere = -1;
			while (i < 3)
			{
				if (intersect_ray_sphere(holder->camera->viewray, holder->sphere[i], &intersection))
					current_sphere = i;
				i++;
			}
			if (current_sphere != -1)
			{
				scaled = vectorScale(intersection, holder->camera->viewray.dir);
				new_start = vectorAdd(holder->camera->viewray.start, scaled);
				if (get_normal(&normal, new_start, holder->sphere[current_sphere].center))
				{
					color = get_light_value(holder, holder->sphere[current_sphere], new_start, normal);
					img_pixel_put(rt, x, y, color_to_trgb(color));
				}
			}
			x++;
		}
		y++;
	}
}*/
