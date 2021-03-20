/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:26:57 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:37:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ray_infinite_cylinder_intersect(t_ray ray,
											t_object *object,
											double *t1,
											double *t2)
{
	t_vector	quadratic;
	t_vector	tmp;
	t_vector	tmp2;
	t_vector	dist;
	t_cylinder	cylinder;

	cylinder = *(t_cylinder *)object->ptr;
	tmp = vector_cross(ray.dir, object->current_direction);
	dist = vector_sub(ray.pos, object->vertex[0]);
	tmp2 = vector_cross(dist, object->current_direction);
	quadratic.x = vector_dot(tmp, tmp);
	quadratic.y = 2 * vector_dot(tmp, tmp2);
	quadratic.z = pow(cylinder.diameter / 2, 2);
	quadratic.z *= vector_dot(object->current_direction,
								object->current_direction);
	quadratic.z = vector_dot(tmp2, tmp2) - quadratic.z;
	return (resolve_quadratic(quadratic, t1, t2));
}

int			check_between_planes(t_ray ray, t_object *object, double t)
{
	t_vector	intersection;
	t_vector	center;
	t_vector	tmp;
	double		dot;
	t_cylinder	cylinder;

	cylinder = *(t_cylinder *)object->ptr;
	intersection = vector_add(ray.pos, vector_mul(t, ray.dir));
	tmp = vector_sub(intersection, object->vertex[0]);
	dot = vector_dot(object->current_direction, tmp);
	if (dot < 0)
		return (0);
	tmp = vector_mul(cylinder.height, object->current_direction);
	center = vector_add(object->vertex[0], tmp);
	tmp = vector_sub(intersection, center);
	dot = vector_dot(object->current_direction, tmp);
	return (dot <= 0);
}

double		ray_cylinder_intersect(t_ray ray,
									t_object *object,
									double t_min,
									double t_max)
{
	double	t1;
	double	t2;
	double	t3;
	double	closest_t;

	closest_t = t_max;
	t3 = ray_cylinder_planes_intersect(ray, object, t_min, t_max);
	if (ray_infinite_cylinder_intersect(ray, object, &t1, &t2))
	{
		if (t1 > t_min && t1 < t_max
			&& check_between_planes(ray, object, t1))
		{
			closest_t = t1;
			if (t2 > t_min && t2 < t_max
				&& check_between_planes(ray, object, t2))
				closest_t = MIN(t1, t2);
		}
		else if (t2 > t_min && t2 < t_max
			&& check_between_planes(ray, object, t2))
			closest_t = t2;
		if (t3 > t_min && t3 < t_max && t3 < closest_t)
			closest_t = t3;
	}
	return (closest_t);
}

t_vector	get_cylinder_normal(t_ray ray,
								t_vector intersection,
								t_object *object)
{
	double		tmp;
	t_vector	vtmp;
	t_cylinder	cylinder;
	t_vector	normal;

	(void)ray;
	cylinder = *(t_cylinder *)object->ptr;
	if (get_caps_normal(intersection, object, &normal))
		return (normal);
	tmp = vector_len(vector_sub(intersection, object->vertex[0]));
	tmp = sqrtf(tmp * tmp - cylinder.diameter * cylinder.diameter / 4);
	vtmp = vector_mul(tmp, object->current_direction);
	normal = vector_add(object->vertex[0], vtmp);
	normal = vector_sub(intersection, normal);
	normal = vector_mul(1 / vector_len(normal), normal);
	return (normal);
}
