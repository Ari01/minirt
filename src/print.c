/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:18:43 by user42            #+#    #+#             */
/*   Updated: 2020/12/15 14:28:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		img_pixel_put(t_rt *rt, int x, int y, int color)
{
	char *dst;

	dst = rt->img.addr + (y * rt->img.line_length + x * (rt->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		get_pixel_color(t_rt *rt, t_holder *holder, void *current_object, double intersection)
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

void		print_object(t_rt *rt, t_holder *holder)
{
	double	intersection;
	void	*current_object;
	int		x;
	int		y;

	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			holder->camera->viewray.start.x = x;
			holder->camera->viewray.start.y = y;
			//holder->camera->viewray.dir = new_vector(0, 0, 1);
			intersection = 20000.0f;
			current_object = get_intersected_object(holder, &intersection);
			if (current_object)
				get_pixel_color(rt, holder, current_object, intersection);
			x++;
		}
		y++;
	}
}
