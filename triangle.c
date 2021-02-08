/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:06:08 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 09:24:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			inside_outside_test(t_vector normal, t_vector v1, t_vector v2, t_vector p)
{
	t_vector	tmp;
	t_vector	edge;
	t_vector	vp;

	edge = vector_sub(v1, v2);
	vp = vector_sub(p, v2);
	tmp = vector_cross(edge, vp);
	if (vector_dot(normal, tmp) < 0)
		return (0);
	return (1);
}

double		ray_triangle_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	t_triangle	triangle;
	t_vector	normal;
	t_vector	intersection;
	double		tmp;
	double		t;

	triangle = *(t_triangle *)object->ptr;
	normal = vector_cross(vector_sub(triangle.p1, triangle.p0), vector_sub(triangle.p2, triangle.p0));
	tmp = vector_dot(normal, ray.dir);
	t = t_max;
	if (tmp > exp(-6) || -tmp > exp(-6))
	{
		t = -(vector_dot(normal, ray.pos) + vector_dot(normal, triangle.p0)) / tmp;
		intersection = vector_add(ray.pos, vector_mul(t, ray.dir));
		if (t <= t_min
			|| !inside_outside_test(normal, triangle.p1, triangle.p0, intersection)
			|| !inside_outside_test(normal, triangle.p2, triangle.p1, intersection)
			|| !inside_outside_test(normal, triangle.p0, triangle.p2, intersection))
			return (t_max);
	}
	return (t);
}

t_vector	get_triangle_normal(t_ray ray, t_vector intersection, t_object *object)
{
	t_triangle	triangle;
	t_vector	p0p1;
	t_vector	p0p2;
	t_vector	normal;

	(void)ray;
	(void)intersection;
	triangle = *(t_triangle *)object->ptr;
	p0p1 = vector_sub(triangle.p1, triangle.p0);
	p0p2 = vector_sub(triangle.p2, triangle.p0);
	normal = vector_cross(p0p1, p0p2);
	if (vector_dot(normal, ray.dir) > 0)
		normal = vector_mul(-1, normal);
	return (normal);
}
