/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:37:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 05:13:43 by user42           ###   ########.fr       */
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
	object->current_direction = vector_mul(1 / vector_len(object->current_direction), object->current_direction);

	plane = *(t_plane *)object->ptr;
	denom = vector_dot(ray.dir, object->current_direction);
	if (denom > exp(-6) || -denom > exp(-6))
	{
		dist = vector_sub(object->position, ray.pos);
		t = vector_dot(dist, object->current_direction) / denom;
	}
	if (t > t_min && t < t_max)
		return (t);
	return (t_max);
}

t_vector	get_plane_normal(t_vector intersection, t_object *object)
{
	(void)intersection;
	return (object->current_direction);
}
/*
void		rotate_plane(int key, t_object *object)
{
	t_plane		*plane;

	plane = (t_plane *)object->ptr;
	if (key == 'q')
		plane->direction.x -= 0.1;
	if (key == 'd')
		plane->direction.x += 0.1;
	if (key == 's')
		plane->direction.z -= 0.1;
	if (key == 'z')
		plane->direction.z += 0.1;
	if (key == CONTROL)
		plane->direction.y -= 0.1;
	if (key == SPACE)
		plane->direction.y += 0.1;
}*/
