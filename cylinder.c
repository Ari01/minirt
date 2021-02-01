/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:26:57 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 19:01:26 by user42           ###   ########.fr       */
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

int			check_between_planes(t_ray ray, t_object *object, double t)
{
	t_vector	intersection;
	double		dot;
	t_vector	center;
	t_cylinder	cylinder;

	cylinder = *(t_cylinder *)object->ptr;
	intersection = vector_add(ray.pos, vector_mul(t, ray.dir));
	dot = vector_dot(object->direction, vector_sub(intersection, object->position));
	if (dot <= 0)
		return (0);
	center = vector_add(object->position, vector_mul(cylinder.height, object->direction));
	dot = vector_dot(object->direction, vector_sub(intersection, center));
	return (dot < 0);
}

int			check_inside_ray(t_ray ray, t_object *object, double t)
{
	t_vector	intersection;
	t_vector	center;
	t_cylinder	cylinder;
	t_vector	vtmp;
	double		dot;

	cylinder = *(t_cylinder *)object->ptr;
	intersection = vector_add(ray.pos, vector_mul(t, ray.dir));
	vtmp = vector_sub(intersection, object->position);
	dot = vector_dot(vtmp, vtmp);
	if (dot >= cylinder.diameter * cylinder.diameter / 4)
		return (0);
	center = vector_add(object->position, vector_mul(cylinder.height, object->direction));
	vtmp = vector_sub(intersection, center);
	dot = vector_dot(vtmp, vtmp);
	if (dot < cylinder.diameter * cylinder.diameter / 4)
		printf("%d\n", dot < cylinder.diameter * cylinder.diameter / 4);
	return (dot < cylinder.diameter * cylinder.diameter / 4);
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

double		ray_cylinder_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	double	t1;
	double	t2;
	double	t3;
	double	closest_t;

	closest_t = t_max;
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
		if (t3 > t_min && t3 < t_max && t3 < closest_t)
			closest_t = t3;
	}
	return (closest_t);
}

t_vector	get_cylinder_normal(t_vector intersection, t_object *object)
{
	double		tmp;
	t_cylinder	cylinder;
	t_vector	normal;

	cylinder = *(t_cylinder *)object->ptr;
	tmp = vector_len(vector_sub(intersection, object->position));
	tmp = sqrtf(tmp * tmp - cylinder.diameter * cylinder.diameter / 4);
	normal = vector_add(object->position, vector_mul(tmp, object->direction));
	return (normal);
}
