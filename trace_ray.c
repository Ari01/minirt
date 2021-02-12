/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:32:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 13:21:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			resolve_quadratic(t_vector v, double *t1, double *t2)
{
	double		discriminant;

	discriminant = v.y * v.y - 4 * v.x * v.z;
	if (discriminant < 0)
	{
		*t1 = 100000.0;
		*t2 = 100000.0;
		return (0);
	}
	else if (!discriminant)
	{
		*t1 = -v.y / (2 * v.x);
		*t2 = -v.y / (2 * v.x);
	}
	else
	{
		*t1 = (-v.y + sqrtf(discriminant)) / (2 * v.x);
		*t2 = (-v.y - sqrtf(discriminant)) / (2 * v.x);
	}
	return (1);
}

double		get_closest_intersection(t_rt *rt, t_object **closest_object, double t_min, double t_max)
{
	t_object	*current_object;
	t_list		*object_list;
	double		closest_t;
	double		t;

	closest_t = t_max;
	object_list = rt->scene.objects;
	int count = 0;
	while (object_list)
	{
		count++;
		current_object = (t_object *)object_list->content;
		t = current_object->intersect(rt->ray, current_object, t_min, t_max);
		if (t < closest_t)
		{
			closest_t = t;
			if (closest_object)
				*closest_object = current_object;
		}
		object_list = object_list->next;
	}
	//printf("count = %d\n", count);
	return (closest_t);
}

t_vector	reflect_ray(t_vector raydir, t_vector normal)
{
	t_vector	reflect;

	reflect = vector_mul(2 * vector_dot(normal, raydir), normal);
	reflect = vector_sub(reflect, raydir);
	return (reflect);
}

t_color		trace_ray(t_rt *rt, int depth)
{
	double		closest_t;
	t_object	*closest_object;
	t_vector	intersection;
	t_vector	normal;
	t_color		color;

	closest_object = NULL;
	closest_t = get_closest_intersection(rt, &closest_object, exp(-6), INFINITY);
	(void)depth;
	if (closest_object)
	{
		intersection = vector_add(rt->ray.pos, vector_mul(closest_t, rt->ray.dir));
		normal = closest_object->get_normal(rt->ray, intersection, closest_object);
		color = compute_light(rt, closest_object, intersection, normal);
		return (color);

	//	return (closest_object->color);
	//	color = closest_object->color;
		//color = color_mul(compute_light(rt, closest_object, intersection, normal), color);
		//color = color_clamp(color_add(color_mul(0.8, color), color_mul(0.2, compute_light(rt, closest_object, intersection, normal))));
	/*	color = color_clamp(color_mix(compute_light(rt, closest_object, intersection, normal), color));
		if (depth == 3 || !closest_object->reflective)
			return (color);
		rt->ray.dir = reflect_ray(vector_mul(-1, rt->camera->direction), normal);
		rt->ray.pos = vector_add(vector_mul(0.1, normal), intersection);
		return (color_clamp(color_add(color_mul(0.5, color), color_mul(0.5, trace_ray(rt, depth + 1)))));
	*/}
	return (new_color(255, 255, 255));
}
