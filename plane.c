/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:37:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 20:01:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		ray_plane_intersect(t_ray ray,
								t_object *object,
								double t_min,
								double t_max)
{
	t_vector	dist;
	double		t;
	double		denom;

	t = t_max;
	denom = vector_dot(object->current_direction, ray.dir);
	if (fabs(denom) > exp(-6))
	{
		dist = vector_sub(object->vertex[0], ray.pos);
		t = vector_dot(dist, object->current_direction) / denom;
	}
	if (t > t_min)
		return (t);
	return (t_max);
}

t_vector	get_plane_normal(t_ray ray, t_vector intersection, t_object *object)
{
	(void)intersection;
	(void)ray;
	return (object->current_direction);
}
