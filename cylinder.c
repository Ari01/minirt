/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:26:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 16:31:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ray_infinite_cylinder_intersect(t_ray ray, t_object *object, double *t1, double *t2)
{
	t_vector	quadratic;
	t_vector	tmp;
	t_vector	tmp2;
	t_vector	dist;

	t_cylinder	cylinder;
	cylinder = *(t_cylinder *)object->ptr;
	tmp = vector_mul(vector_dot(ray.dir, object->direction), object->direction);
	tmp = vector_sub(ray.dir, tmp);
	dist = vector_sub(ray.pos, object->position);
	tmp2 = vector_mul(vector_dot(dist, object->direction), object->direction);
	tmp2 = vector_sub(dist, tmp2);
	quadratic.x = vector_dot(tmp, tmp);
	quadratic.y = 2 * vector_dot(tmp, tmp2);
	quadratic.z = vector_dot(tmp2, tmp2) - pow(cylinder.diameter / 2, 2);
	return (resolve_quadratic(quadratic, t1, t2));
}

double		ray_cylinder_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	double	t1;
	double	t2;
/*	double	t3;
	double	t4;*/
	double	closest_t;

	closest_t = t_max;
	if (ray_infinite_cylinder_intersect(ray, object, &t1, &t2))
	{
		if (t1 > t_min && t1 < t_max)
		{
			closest_t = t1;
			if (t2 > t_min && t2 < t_max)
				closest_t = MIN(t1, t2);
		}
		else if (t2 > t_min && t2 < t_max)
			closest_t = t2;
	}
	return (closest_t);
}
