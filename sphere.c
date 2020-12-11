/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:32:32 by user42            #+#    #+#             */
/*   Updated: 2020/12/11 18:25:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>
t_sphere	init_sphere(t_vector center, double radius)
{
	t_sphere sphere;

	sphere.center = center;
	sphere.radius = radius;
	return (sphere);
}

int			get_intersection(double B, double discriminant, double *intersection)
{
	double s0;
	double s1;

	s0 = (-B + sqrtf(discriminant)) / 2;
	s1 = (-B - sqrtf(discriminant)) / 2;
	if (s0 > s1)
		s0 = s1;
	if (s0 > 0.001f && s0 < *intersection)
	{
		*intersection = s0;
		return (s0);
	}
	return (s1);
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
	if (discriminant < 0)
		return (0);
	return (get_intersection(b, discriminant, intersection));
}

// TODO : finish reflection
void		print_sphere(t_rt *rt, t_sphere sp, t_ray ray)
{
	double	intersection;
	t_color c;
	t_light light;
	t_vector normal;
	t_vector new_start;
	t_vector scaled;

	light.pos = new_vector(-40, 0, 30);
	light.intensity = 0.7;
	light.color = new_color(255, 255, 255);
	intersection = 20000.0f;
	ray.start.y = 0;
	while (ray.start.y < rt->height)
	{
		ray.start.x = 0;
		while (ray.start.x < rt->width)
		{
			c.red = 0;
			c.green = 0;
			c.blue = 0;
			if (intersect_ray_sphere(ray, sp, &intersection))
			{
				scaled = vectorScale(intersection, ray.dir);
				new_start = vectorAdd(ray.start, scaled);
				normal = vectorSub(new_start, sp.center);
				img_pixel_put(rt, ray.start.x, ray.start.y, 0x00FF0000);
			}
			ray.start.x++;
		}
		ray.start.y++;
	}
}
