/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:19:13 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 16:50:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			compute_diffuse(t_vector light_vector,
								double intensity,
								t_vector normal)
{
	double	n_dot_l;

	n_dot_l = MAX(0, vector_dot(normal, light_vector));
	intensity *= n_dot_l / (vector_len(normal) * vector_len(light_vector));
	return (intensity);
}

double			compute_specular(double spec,
								t_vector viewray_dir,
								t_vector normal,
								t_vector light_vector)
{
	t_vector	reflect;
	double		r_dot_v;
	double		tmp;
	double		intensity;

	intensity = 0;
	if (spec != -1)
	{
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
	}
	return (intensity);
}

int				in_shadow(t_rt *rt, t_vector light_vector)
{
	double	t_max;

	t_max = vector_len(light_vector);
	rt->ray.dir = light_vector;
	rt->ray.dir = vector_normalize(rt->ray.dir);
	if (get_closest_intersection(rt, NULL, exp(-6), t_max) == t_max)
		return (0);
	return (1);
}

t_color			add_light_colors(t_rt *rt,
								t_list *light_list,
								t_object *object,
								t_vector normal)
{
	double		intensity;
	double		spec;
	t_light		current_light;
	t_vector	light_vector;
	t_color		color;

	color = new_color(0, 0, 0);
	while (light_list)
	{
		current_light = *(t_light *)light_list->content;
		light_vector = vector_sub(current_light.position, rt->ray.pos);
		if (!in_shadow(rt, light_vector))
		{
			intensity = compute_diffuse(light_vector, current_light.intensity,
										normal);
			spec = compute_specular(object->specular, rt->camera->direction,
									normal, light_vector);
			intensity += current_light.intensity * spec;
			color = color_clamp(
						color_add(color,
							color_scale(intensity, current_light.color)));
		}
		light_list = light_list->next;
	}
	return (color);
}

t_color			compute_light(t_rt *rt,
								t_object *object,
								t_vector intersection,
								t_vector normal)
{
	t_color		color;
	double		intensity;

	intensity = rt->scene.ambiant_light.intensity;
	color = color_scale(intensity, rt->scene.ambiant_light.color);
	rt->ray.pos = intersection;
	color = color_clamp(
				color_add(color,
					add_light_colors(rt, rt->scene.light, object, normal)));
	return (color);
}
