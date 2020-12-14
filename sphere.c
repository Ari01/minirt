/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:32:32 by user42            #+#    #+#             */
/*   Updated: 2020/12/14 17:18:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>
t_sphere	new_sphere(t_vector pos, double radius, t_color color)
{
	t_sphere sphere;

	sphere.pos = pos;
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
	dist = vectorSub(ray.start, sp.pos);
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
	void	*current_object;
	int		x;
	int		y;

	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			holder->camera->viewray.start = new_vector(x, y, -2000);
			holder->camera->viewray.dir = new_vector(0, 0, 1);
			intersection = 20000.0f;
			current_object = get_intersected_object(holder, &intersection);
			if (current_object)
				add_pixel_color(rt, holder, current_object, intersection);
			x++;
		}
		y++;
	}
}
