/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:32:35 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 18:25:21 by user42           ###   ########.fr       */
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
	while (object_list)
	{
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
	return (closest_t);
}

t_color		trace_ray(t_rt *rt)
{
	double		closest_t;
	t_object	*closest_object;
	t_vector	intersection;
	t_vector	normal;

	rt->ray.pos = rt->camera->position;
	rt->ray.dir = rt->camera->direction;
	closest_object = NULL;
	closest_t = get_closest_intersection(rt, &closest_object, 1, 100000.0);
	if (closest_object != NULL)
	{
		rt->ray.dir = vector_mul(closest_t, rt->ray.dir);
		intersection = vector_add(rt->ray.pos, rt->ray.dir);
		normal = closest_object->get_normal(intersection, closest_object);
		//return (closest_object->color);
		return (color_mul(compute_light(rt, closest_object, intersection, normal), closest_object->color));
	}
	return (new_color(0, 0, 0));
}
