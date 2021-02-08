/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:00:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/06 19:04:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			check_inside_ray(t_ray ray, t_object *object, double t)
{
	t_vector	intersection;
	t_vector	center;
	t_cylinder	cylinder;
	t_vector	vtmp;

	cylinder = *(t_cylinder *)object->ptr;
	intersection = vector_add(ray.pos, vector_mul(t, ray.dir));
	vtmp = vector_sub(intersection, object->position);
	if (vector_len(vtmp) < cylinder.diameter * cylinder.diameter / 4)
		return (1);
	center = vector_add(object->position, vector_mul(cylinder.height, object->direction));
	vtmp = vector_sub(intersection, center);
	return (vector_len(vtmp) < cylinder.diameter * cylinder.diameter / 4);
}

double		ray_cylinder_planes_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	double		t1;
	double		t2;
	t_vector	center;
	t_cylinder	cylinder;
	t_object	tmp;

	cylinder = *(t_cylinder *)object->ptr;
	t1 = ray_plane_intersect(ray, object, t_min, t_max);
	center = vector_add(object->position, vector_mul(cylinder.height, object->direction));
	tmp.position = center;
	tmp.current_direction = vector_mul(-1, object->direction);
	t2 = ray_plane_intersect(ray, &tmp, t_min, t_max);
	if (t1 > t_min && t1 < t_max && check_inside_ray(ray, object, t1))
	{
		if (t2 > t_min && t2 < t_max && check_inside_ray(ray, object, t2))
			t1 = MIN(t1, t2);
	}
	else if (t2 > t_min && t2 < t_max && check_inside_ray(ray, object, t2))
		t1 = t2;
	else
		t1 = t_max;
	return (t1);
}

int		get_caps_normal(t_vector intersection, t_object *object, t_vector *normal)
{
	t_vector	center;
	t_vector	dist;
	t_cylinder	cylinder;

	cylinder = *(t_cylinder *)object->ptr;
	center = vector_add(object->position, vector_mul(cylinder.height, object->direction));
	dist = vector_sub(intersection, center);
	if (vector_len(dist) < cylinder.diameter / 2)
	{
		*normal = object->direction;
		return (1);
	}
	dist = vector_sub(intersection, object->position);
	if (vector_len(dist) < cylinder.diameter / 2)
	{
		*normal = vector_mul(-1, object->direction);
		return (1);
	}
	return (0);
}