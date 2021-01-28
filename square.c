/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:23:08 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 18:24:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		ray_square_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	double		t;
	t_vector	intersection;
	t_square	square;

	square = *(t_square *)object->ptr;
	t = ray_plane_intersect(ray, object, t_min, t_max);
	if (t < t_max)
	{
		ray.dir = vector_mul(t, ray.dir);
		intersection = vector_add(ray.pos, ray.dir);
		if (intersection.x <= object->position.x + square.height / 2
			&& intersection.x >= object->position.x - square.height / 2
			&& intersection.y <= object->position.y + square.height / 2
			&& intersection.y >= object->position.y - square.height / 2
			&& intersection.z <= object->position.z + square.height / 2
			&& intersection.z >= object->position.z - square.height / 2)
			return (t);
	}
	return (t_max);
}
