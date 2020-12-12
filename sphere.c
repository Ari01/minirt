/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:32:32 by user42            #+#    #+#             */
/*   Updated: 2020/12/12 18:59:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>
t_sphere	new_sphere(t_vector center, double radius)
{
	t_sphere sphere;

	sphere.center = center;
	sphere.radius = radius;
	return (sphere);
}

double		get_intersection(double b, double discriminant, double intersection)
{
	double s0;
	double s1;

	s0 = (-b + sqrtf(discriminant)) / 2;
	s1 = (-b - sqrtf(discriminant)) / 2;
	if (s0 > s1)
		s0 = s1;
	if (s0 > 0.001f && s0 < intersection)
		return (s0);
	return (intersection);
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
	(void)intersection;

	a = vectorMul(ray.dir, ray.dir);
	dist = vectorSub(ray.start, sp.center);
	b = 2 * vectorMul(ray.dir, dist);
	c = vectorMul(dist, dist) - sp.radius * sp.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0.f)
		return (0);
	*intersection = get_intersection(b, discriminant, *intersection);
	return (1);
}

void		print_sphere(t_rt *rt, t_sphere sp, t_camera camera)
{
	double	intersection;
	t_light light;
	t_vector normal;
	t_vector new_start;
	t_vector scaled;
	t_color	color;

	light = new_light(new_vector(-40, 0, 30), new_color(255, 255, 255), 0.7);
	intersection = 20000.0f;
	camera.viewray.start.y = 0;
	sp.color.red = 255;
	sp.color.green = 0;
	sp.color.blue = 0;
	while (camera.viewray.start.y < rt->height)
	{
		camera.viewray.start.x = 0;
		while (camera.viewray.start.x < rt->width)
		{
			if (intersect_ray_sphere(camera.viewray, sp, &intersection))
			{
				scaled = vectorScale(intersection, camera.viewray.dir);
				new_start = vectorAdd(camera.viewray.start, scaled);
				if (!get_normal(&normal, new_start, sp.center))
					break;
				color.red = sp.color.red * light.intensity;
				color.green = sp.color.green * light.intensity;
				color.blue = sp.color.blue * light.intensity;
				img_pixel_put(rt, camera.viewray.start.x, camera.viewray.start.y, color_to_trgb(color));
			}
			camera.viewray.start.x++;
		}
		camera.viewray.start.y++;
	}
}
