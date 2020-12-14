/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:33:58 by user42            #+#    #+#             */
/*   Updated: 2020/12/14 13:59:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light		new_light(t_vector pos, t_color color, double intensity)
{
	t_light light;

	light.pos = pos;
	light.intensity = intensity;
	light.color = color;
	return (light);
}

#include <stdio.h>
t_color		get_light_value(t_holder *holder, t_sphere sp, t_vector new_start, t_vector normal)
{
	t_vector	dist;
	t_ray		light_ray;
	double		t;
	double		lambert;
	t_color		color;
	int i;

	color = new_color(0, 0, 0);
	i = 0;
	while (i < 3)
	{
		dist = vectorSub(holder->light[i].pos, new_start);
		if (vectorMul(normal, dist) >= 0.0f)
		{
			t = sqrtf(vectorMul(dist, dist));
			light_ray.start = new_start;
			light_ray.dir = vectorScale(1 / t, dist);

			int j;
			int in_shadow;

			j = 0;
			in_shadow = 0;
			while (j < 3)
			{
				if (intersect_ray_sphere(light_ray, holder->sphere[j], &t))
				{
					in_shadow = 1;
					break;
				}
				j++;
			}
			if (!in_shadow)
			{
				lambert = vectorMul(light_ray.dir, normal);
				color.red += lambert * holder->light[i].color.red * sp.color.red * holder->light[i].intensity;
				color.green += lambert * holder->light[i].color.green * sp.color.green * holder->light[i].intensity;
				color.blue += lambert * holder->light[i].color.blue * sp.color.blue * holder->light[i].intensity;
			}
		}
		i++;
	}
	color.red = min(color.red * 255, 255);
	color.green = min(color.green * 255, 255);
	color.blue = min(color.blue * 255, 255);
	return (color);
}
