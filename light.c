/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:33:58 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 13:49:04 by user42           ###   ########.fr       */
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
	t_color		color;
	t_vector	dist;
	t_ray		light_ray;
	double		t;
	double		lambert;
	
	color.red = 0;
	color.green = 0;
	color.blue = 0;

	int i;

	i = 0;
	while (i < 2)
	{
		dist = vectorSub(holder->light[i].pos, new_start);
		if (vectorMul(normal, dist) <= 0.0f)
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
				color.red += lambert * holder->light[i].color.red * holder->light[i].intensity * sp.color.red;
				color.green += lambert * holder->light[i].color.green * holder->light[i].intensity * sp.color.green;
				color.blue += lambert * holder->light[i].color.blue * holder->light[i].intensity * sp.color.blue;
			}
		}
		i++;
	}
	return (color);
}
