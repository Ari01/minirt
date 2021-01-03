/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:32:35 by user42            #+#    #+#             */
/*   Updated: 2021/01/03 15:41:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_color		trace_ray(t_rt *rt)
{
	double		closest_t;
	t_object	*closest_object;
	t_vector	intersection;
	t_vector	normal;
	t_ray		viewray;

	viewray.pos = rt->camera->position;
	viewray.dir = rt->camera->direction;
	closest_t = get_closest_intersection(t_rt *rt, closest_object, 0, 100000.0);
	viewray.dir = vector_mul(closest_t, viewray.dir);
	intersection = vector_add(viewray.pos, viewray.dir);
	normal = vector_sub(intersection, closest_object)
}
