/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:26:57 by user42            #+#    #+#             */
/*   Updated: 2021/02/10 07:38:20 by user42           ###   ########.fr       */
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
	tmp = vector_cross(ray.dir, object->direction);
	dist = vector_sub(ray.pos, object->position);
	tmp2 = vector_cross(dist, object->direction);
	quadratic.x = vector_dot(tmp, tmp);
	quadratic.y = 2 * vector_dot(tmp, tmp2);
	quadratic.z = vector_dot(tmp2, tmp2) - (pow(cylinder.diameter / 2, 2)
				* vector_dot(object->direction, object->direction));
	return (resolve_quadratic(quadratic, t1, t2));
}

int			check_between_planes(t_ray ray, t_object *object, double t)
{
	t_vector	intersection;
	double		dot;
	t_vector	center;
	t_cylinder	cylinder;

	cylinder = *(t_cylinder *)object->ptr;
	intersection = vector_add(ray.pos, vector_mul(t, ray.dir));
	dot = vector_dot(object->direction, vector_sub(intersection, object->position));
	if (dot < 0)
		return (0);
	center = vector_add(object->position, vector_mul(cylinder.height, object->direction));
	dot = vector_dot(object->direction, vector_sub(intersection, center));
	return (dot <= 0);
}

double		ray_cylinder_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	double		t1;
	double		t2;
	double		t3;
	double		closest_t;
	t_cylinder	cylinder;

	closest_t = t_max;
	cylinder = *(t_cylinder *)object->ptr;
	if (cylinder.caps)
		t3 = ray_cylinder_planes_intersect(ray, object, t_min, t_max);
	if (ray_infinite_cylinder_intersect(ray, object, &t1, &t2))
	{
		if (t1 > t_min && t1 < t_max && check_between_planes(ray, object, t1))
		{
			closest_t = t1;
			if (t2 > t_min && t2 < t_max && check_between_planes(ray, object, t2))
				closest_t = MIN(t1, t2);
		}
		else if (t2 > t_min && t2 < t_max && check_between_planes(ray, object, t2))
			closest_t = t2;
		if (cylinder.caps && t3 > t_min && t3 < t_max && t3 < closest_t)
			closest_t = t3;
	}
	return (closest_t);
}

t_vector	get_cylinder_normal(t_ray ray, t_vector intersection, t_object *object)
{
	double		tmp;
	t_cylinder	cylinder;
	t_vector	normal;

	cylinder = *(t_cylinder *)object->ptr;
	if (cylinder.caps && get_caps_normal(intersection, object, &normal))
		return (normal);
	tmp = vector_len(vector_sub(intersection, object->position));
	tmp = sqrtf(tmp * tmp - cylinder.diameter * cylinder.diameter / 4);
	normal = vector_add(object->position, vector_mul(tmp, object->direction));
	normal = vector_sub(intersection, normal);
	normal = vector_mul(1 / vector_len(normal), normal);
	if (vector_dot(ray.dir, normal) <= 0)
		vector_mul(-1, normal);
	return (normal);
}
