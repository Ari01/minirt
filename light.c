/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:33:58 by user42            #+#    #+#             */
/*   Updated: 2020/12/12 17:41:01 by user42           ###   ########.fr       */
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

t_color		get_light_value(t_light light, t_vector new_start, t_vector normal)
{
	t_color		color;
	t_vector	dist;
	t_ray		light_ray;
	double		t;
	double		lambert;
	
	color.red = 0;
	color.green = 0;
	color.blue = 0;
	dist = vectorSub(light.pos, new_start);
	if (vectorMul(normal, dist) <= 0.0f)
	{
		t = sqrtf(vectorMul(dist, dist));
		light_ray.start = new_start;
		light_ray.dir = vectorScale(1 / t, dist);
		lambert = vectorMul(light_ray.dir, normal);
		color.red += lambert * light.color.red * light.intensity / 255;
		color.green += lambert * light.color.green * light.intensity / 255;
		color.blue += lambert * light.color.blue * light.intensity / 255;
	}
	return (color);
}
