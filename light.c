/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:33:58 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 19:16:20 by user42           ###   ########.fr       */
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
t_color		get_light_value(t_holder *holder, t_sphere sp, t_vector new_start, t_vector normal, double coef)
{
	t_vector	dist;
	t_ray		light_ray;
	double		t;
	double		lambert;
	int i;

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
				lambert = vectorMul(light_ray.dir, normal) * coef;
				holder->current_color.red += lambert * holder->light[i].color.red * sp.color.red;
				holder->current_color.green += lambert * holder->light[i].color.green * sp.color.green;
				holder->current_color.blue += lambert * holder->light[i].color.blue * sp.color.blue;
			}
		}
		i++;
	}
	return (holder->current_color);
}
