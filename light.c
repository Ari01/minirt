/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:19:13 by user42            #+#    #+#             */
/*   Updated: 2021/02/11 09:30:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ambiant_light	init_ambiant_light()
{
	t_ambiant_light l;

	l.intensity = -1;
	return (l);
}

/*
double			compute_diffuse(t_vector light_vector, t_vector normal)
{
	double	n_dot_l;
	double	intensity;

	intensity = 0;
	n_dot_l = vector_dot(normal, light_vector);
	if (n_dot_l > 0.0001)
		intensity = n_dot_l / (vector_len(normal) * vector_len(light_vector));
	return (intensity);
}*/

double			compute_diffuse(t_light light, t_vector light_vec, double len, t_vector normal)
{
	double	dot;
	double	r2;

	r2 = len * len;
	dot = vector_dot(normal, light_vec);
	return (0.18 * light.intensity * 1000 * dot / (r2 * M_PI));
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
	double		intensity;
	t_vector	light_vector;
	t_light		current_light;
	t_list		*light_list;
	t_color		color;
	
	color = color_mul(rt->scene.ambiant_light.intensity, rt->scene.ambiant_light.color);
	light_list = rt->scene.light;
	rt->ray.pos = intersection;
	while (light_list)
	{
		current_light = *(t_light *)light_list->content;
		light_vector = vector_sub(current_light.position, intersection);
		rt->ray.dir = light_vector;
		if (get_closest_intersection(rt, NULL, exp(-6), 1) == 1)
		{
			intensity = compute_diffuse(current_light, light_vector, vector_len(light_vector), normal) * current_light.intensity;
			if (object->specular != -1)
				intensity += compute_specular(object->specular, rt->camera->direction, normal, light_vector) * current_light.intensity;
		}
		color = color_mix(color_mul(intensity, current_light.color), color);
		printf("color = %f %f %f\n", color.r, color.g, color.b);
		light_list = light_list->next;
	}
	return (color);
}
