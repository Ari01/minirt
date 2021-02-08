/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:35:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/04 20:25:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			ray_sphere_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	t_sphere	sp;
	t_vector	quadratic;
	t_vector	dist;
	double		t1;
	double		t2;

	sp = *(t_sphere *)object->ptr;
	dist = vector_sub(ray.pos, object->position);
	quadratic.x = vector_dot(ray.dir, ray.dir);
	quadratic.y = 2 * vector_dot(dist, ray.dir);
	quadratic.z = vector_dot(dist, dist) - (sp.diameter / 2) * (sp.diameter / 2);
	if (!resolve_quadratic(quadratic, &t1, &t2))
		return (t_max);
	if (t1 > t_min && t1 < t_max)
	{
		if (t1 < t2)
			return (t1);
		if (t2 > t_min && t2 < t_max)
			return (t2);
		return (t1);
	}
	return (t_max);
}

t_vector	get_sphere_normal(t_ray ray, t_vector intersection, t_object *object)
{
	t_vector normal;

	normal = vector_sub(intersection, object->position);
	normal = vector_mul(1 / vector_len(normal), normal);
	(void)ray;
	return (normal);
}

