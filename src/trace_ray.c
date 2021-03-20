/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:32:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 20:59:44 by user42           ###   ########.fr       */
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

double		get_closest_intersection(t_rt *rt,
									t_object **closest_object,
									double t_min,
									double t_max)
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

t_vector	reflect_ray(t_vector raydir, t_vector normal)
{
	t_vector	reflect;

	raydir = vector_mul(-1, raydir);
	reflect = vector_mul(2 * vector_dot(normal, raydir), normal);
	reflect = vector_sub(reflect, raydir);
	return (reflect);
}

t_color		trace_reflect(t_rt *rt, t_object *ohit, t_color color, int depth)
{
	t_color	reflect;

	color = color_scale(1 - ohit->reflective, color);
	reflect = color_scale(ohit->reflective, trace_ray(rt, depth + 1));
	return (color_clamp(color_add(color, reflect)));
}

t_color		trace_ray(t_rt *rt, int depth)
{
	double		closest_t;
	t_object	*ohit;
	t_vector	phit;
	t_vector	normal;
	t_color		color;

	ohit = NULL;
	closest_t = get_closest_intersection(rt, &ohit, exp(-6), INFINITY);
	color = new_color(0, 0, 0);
	if (ohit)
	{
		phit = vector_mul(closest_t, rt->ray.dir);
		phit = vector_add(rt->ray.pos, phit);
		normal = ohit->get_normal(rt->ray, phit, ohit);
		color = ohit->color;
		color = color_mix(color, compute_light(rt, ohit, phit, normal));
		if (depth == 3 || !ohit->reflective)
			return (color);
		rt->ray.dir = reflect_ray(rt->camera->direction, normal);
		rt->ray.pos = vector_add(vector_mul(0.1, normal), phit);
		color = trace_reflect(rt, ohit, color, depth);
		return (color);
	}
	return (color);
}
