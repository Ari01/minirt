/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:44:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/02 15:17:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_resolution(char **split, t_rt *rt)
{
	if (rt->width != -1 || rt->height != -1
		|| !split[1] || !split[2] || split[3])
		return (0);
	rt->width = ft_atod(split[1]);
	rt->height = ft_atod(split[2]);
	if (rt->width <= 0 || rt->height <= 0)
		return (0);
	return (1);
}

int		set_ambiant_light(char **split, t_rt *rt)
{
	char			**color;
	t_ambiant_light	ambiant_light;

	if (rt->scene.ambiant_light.intensity != -1
		|| !split[1] || !split[2] || split[3])
		return (0);
	color = ft_split(split[2], ",");
	ambiant_light.intensity = ft_atod(split[1]);
	if (!set_color(color, &ambiant_light.color) || ambiant_light.intensity < 0
		|| ambiant_light.intensity > 1)
		return (0);
	rt->scene.ambiant_light = ambiant_light;
	return (1);
}

int		set_camera(char **split, t_rt *rt)
{
	char		**coord;
	char		**direction;
	t_camera	*camera;
	
	camera = malloc(sizeof(*camera));
	if (!camera || !split[1] || !split[2] || !split[3] || split[4])
		return (0);
	coord = ft_split(split[1], ",");
	direction = ft_split(split[2], ",");
	camera->fov = ft_atod(split[3]);
	if (!set_coord(coord, &camera->position) || !set_coord(direction, &camera->direction)
		|| !correct_direction(camera->direction) || camera->fov < 0 || camera->fov > 180)
		return (0);
	if (rt->scene.camera == NULL)
		rt->camera = camera;
	ft_lstadd_front(&rt->scene.camera, ft_lstnew(camera));
	return (1);
}

int		set_light(char **split, t_rt *rt)
{
	char		**coord;
	char		**color;
	t_light		*light;

	light = malloc(sizeof(*light));
	if (!light || !split[1] || !split[2] || !split[3] || split[4])
		return (0);
	coord = ft_split(split[1], ",");
	color = ft_split(split[3], ",");
	light->intensity = ft_atod(split[2]);
	if (!set_coord(coord, &light->position) || !set_color(color, &light->color)
		|| light->intensity < 0 || light->intensity > 1)
		return (0);
	ft_lstadd_front(&rt->scene.light, ft_lstnew(light));
	return (1);
}
