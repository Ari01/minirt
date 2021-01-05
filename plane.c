/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:37:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 18:45:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		ray_plane_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	t_vector	dist;
	t_plane		plane;
	double		t;
	double		denom;

	t = t_max;
	ray.dir = vector_mul(1 / vector_len(ray.dir), ray.dir);
	plane.direction = vector_mul(1 / vector_len(plane.direction), plane.direction);

	plane = *(t_plane *)object->ptr;
	denom = vector_dot(ray.dir, plane.direction);
	if (denom > exp(-6) || -denom > exp(-6))
	{
		dist = vector_sub(object->position, ray.pos);
		t = vector_dot(dist, plane.direction) / denom;
	}
	if (t > t_min && t < t_max)
		return (t);
	return (t_max);
}

t_vector	get_plane_normal(t_vector intersection, t_object *object)
{
	t_plane plane;

	(void)intersection;
	plane = *(t_plane *)object->ptr;
	return (plane.direction);
}
