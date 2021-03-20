/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:06:08 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 09:28:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			left_right_test(t_vector normal,
								t_vector v1,
								t_vector v2,
								t_vector p)
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

int			inside_outside_test(t_vector normal,
								t_vector intersection,
								t_object *object)
{
	t_vector v0;
	t_vector v1;
	t_vector v2;

	v0 = object->vertex[0];
	v1 = object->vertex[1];
	v2 = object->vertex[2];
	return (left_right_test(normal, v1, v0, intersection)
			&& left_right_test(normal, v0, v2, intersection)
			&& left_right_test(normal, v2, v1, intersection));
}

double		ray_triangle_intersect(t_ray ray,
									t_object *object,
									double t_min,
									double t_max)
{
	t_vector	normal;
	t_vector	intersection;
	t_vector	vtmp;
	double		denom;
	double		t;

	normal = vector_sub(object->vertex[0], object->vertex[1]);
	vtmp = vector_sub(object->vertex[0], object->vertex[2]);
	normal = vector_cross(normal, vtmp);
	denom = vector_dot(normal, ray.dir);
	t = t_max;
	if (fabs(denom) > exp(-6))
	{
		t = vector_dot(normal, ray.pos);
		t -= vector_dot(normal, object->vertex[0]);
		t = -t / denom;
		intersection = vector_add(ray.pos, vector_mul(t, ray.dir));
		if (t <= t_min || !inside_outside_test(normal, intersection, object))
			return (t_max);
	}
	return (t);
}

t_vector	get_triangle_normal(t_ray ray,
								t_vector intersection,
								t_object *object)
{
	t_vector	p0p1;
	t_vector	p0p2;
	t_vector	normal;

	(void)ray;
	(void)intersection;
	p0p1 = vector_sub(object->vertex[1], object->vertex[0]);
	p0p2 = vector_sub(object->vertex[2], object->vertex[0]);
	normal = vector_cross(p0p1, p0p2);
	return (normal);
}
