/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:32:32 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 19:15:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>
t_sphere	new_sphere(t_vector center, double radius, t_color color)
{
	t_sphere sphere;

	sphere.center = center;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

int			get_intersection(double a, double b, double discriminant, double *intersection)
{
	double s0;
	double s1;

	s0 = (-b + sqrtf(discriminant)) / (2 * a);
	s1 = (-b - sqrtf(discriminant)) / (2 * a);
	if (s0 > s1)
		s0 = s1;
	if (s0 > 0.001f && s0 < *intersection)
	{
		*intersection = s0;
		return (1);
	}
	return (0);
}

/*
** Formula ray/sphere intersection :
** At² + Bt + C = 0
** d.dt² + 2d.(p0 - c)t + (p0 - c). (p0 - c) - r² = 0
** with d = ray direction, p0 = ray start vector, c = sphere center vector, r = sphere ray
** We calculate the discriminant and if it's >= 0 then we have at least 1 intersection
*/
int			intersect_ray_sphere(t_ray ray, t_sphere sp, double *intersection)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_vector	dist;

	a = vectorMul(ray.dir, ray.dir);
	dist = vectorSub(ray.start, sp.center);
	b = 2 * vectorMul(ray.dir, dist);
	c = vectorMul(dist, dist) - sp.radius * sp.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0.f)
		return (0);
	return (get_intersection(a, b, discriminant, intersection));
}

void		print_sphere(t_rt *rt, t_holder *holder)
{
	double	intersection;
	int		depth;
	t_vector normal;
	t_vector new_start;
	t_vector scaled;
	double	reflection[3];
	double	coef;
	int x,y;

	reflection[0] = 0.2;
	reflection[1] = 0.5;
	reflection[2] = 0.9;
	y = 0;

	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			holder->camera->viewray.start.x = x;
			holder->camera->viewray.start.y = y;
			holder->camera->viewray.start.z = -2000;
			holder->camera->viewray.dir.x = 0;
			holder->camera->viewray.dir.y = 0;
			holder->camera->viewray.dir.z = 1;
			holder->current_color.red = 0;
			holder->current_color.green = 0;
			holder->current_color.blue = 0;
			depth = 0;
			coef = 1.0;
			while (coef > 0.0f && depth < 15)
			{
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
				if (current_sphere == -1)
					break;
				scaled = vectorScale(intersection, holder->camera->viewray.dir);
				new_start = vectorAdd(holder->camera->viewray.start, scaled);
				if (!get_normal(&normal, new_start, holder->sphere[current_sphere].center))
					break;
				holder->current_color = get_light_value(holder, holder->sphere[current_sphere], new_start, normal, coef);
			//	img_pixel_put(rt, holder->camera->viewray.start.x, holder->camera->viewray.start.y, color_to_trgb(holder->sphere[current_sphere].color));
				holder->camera->viewray.start = new_start;
				double reflect = 2.0f * vectorMul(holder->camera->viewray.dir, normal);
				holder->camera->viewray.dir = vectorSub(holder->camera->viewray.dir, vectorScale(reflect, normal));
				coef *= reflection[current_sphere];
				depth++;
			}
			holder->current_color.red = min(holder->current_color.red * 255, 255);
			holder->current_color.green = min(holder->current_color.green * 255, 255);
			holder->current_color.blue *= min(holder->current_color.blue * 255, 255);	
			img_pixel_put(rt, x, y, color_to_trgb(holder->current_color));
			x++;
		}
		y++;
	}
}
