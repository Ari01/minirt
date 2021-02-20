/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:19:13 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 17:29:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ambiant_light	init_ambiant_light()
{
	t_ambiant_light l;

	l.intensity = -1;
	return (l);
}

double			compute_diffuse(t_vector light_vector, double intensity, t_vector normal)
{
	double	n_dot_l;

	n_dot_l = MAX(0, vector_dot(normal, light_vector));
	intensity *= n_dot_l / (vector_len(normal) * vector_len(light_vector));
	return (intensity);
}

double			compute_specular(double spec, t_vector viewray_dir, t_vector normal, t_vector light_vector)
{
	t_vector	reflect;
	double		r_dot_v;
	double		tmp;
	double		intensity;

	intensity = 0;
	tmp = vector_dot(normal, light_vector) * 2;
	reflect = vector_mul(tmp, normal);
	reflect = vector_sub(reflect, light_vector);
	viewray_dir = vector_mul(-1, viewray_dir);
	r_dot_v = vector_dot(reflect, viewray_dir);
	if (r_dot_v > 0)
	{
		tmp = r_dot_v / (vector_len(reflect) * vector_len(viewray_dir));
		intensity = pow(tmp, spec);
	}
	return (intensity);
}

t_color			compute_light(t_rt *rt, t_object *object, t_vector intersection, t_vector normal)
{
	t_color		color;
	double		intensity;
	t_vector	light_vector;
	t_light		current_light;
	t_list		*light_list;
	
	color = color_scale(rt->scene.ambiant_light.intensity, rt->scene.ambiant_light.color);
	rt->ray.pos = intersection;
	light_list = rt->scene.light;
	while (light_list)
	{
		current_light = *(t_light *)light_list->content;
		light_vector = vector_sub(current_light.position, intersection);
		rt->ray.dir = light_vector;
		rt->ray.dir = vector_mul(1 / vector_len(rt->ray.dir), rt->ray.dir);
		if (get_closest_intersection(rt, NULL, exp(-6), vector_len(light_vector)) == vector_len(light_vector))
		{
			intensity = compute_diffuse(light_vector, current_light.intensity, normal);
			if (object->specular != -1)
				intensity += compute_specular(object->specular, rt->camera->direction, normal, light_vector) * current_light.intensity;
			color = color_clamp(color_add(color, color_scale(intensity, current_light.color)));
		}
		light_list = light_list->next;
	}
	return (color);
}
