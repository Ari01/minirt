/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:37:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 17:03:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		ray_plane_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	t_vector	dist;
	double		t;
	double		denom;

	t = t_max;
	denom = vector_dot(object->current_direction, ray.dir);
	if (denom > exp(-6) || -denom > exp(-6))
	{
		dist = vector_sub(object->vertex[0], ray.pos);
		t = vector_dot(dist, object->current_direction) / denom;
	}
	if (t > t_min && t < t_max)
		return (t);
	return (t_max);
}

t_vector	get_plane_normal(t_ray ray, t_vector intersection, t_object *object)
{
	(void)intersection;
	if (vector_dot(object->current_direction, ray.dir) > 0)
		return (vector_mul(-1, object->current_direction));
	return (object->current_direction);
}
