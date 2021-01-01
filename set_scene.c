/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:44:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/01 15:35:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_resolution(char **split, t_rt *rt)
{
	if (rt->width != -1 || rt->height != -1)
		print_error_msg("resolution 'R' defined twice");
	if (!split[1] || !split[2] || split[3])
	{
		string_array_free(split);
		print_error_msg("invalid_resolution format");
	}
	rt->width = ft_atod(split[1]);
	rt->height = ft_atod(split[2]);
	if (rt->width <= 0 || rt->height <= 0)
	{
		string_array_free(split);
		print_error_msg("invalid resolution settings");
	}
}

void	set_ambiant_light(char **split, t_rt *rt)
{
	char			**color;
	t_ambiant_light	ambiant_light;

	if (rt->scene.ambiant_light.intensity != -1)
		print_error_msg("ambiant light 'A' defined twice");
	if (!split[1] || !split[2] || split[3])
		print_error_msg("invalid ambiant light format");
	color = ft_split(split[2], ",");
	ambiant_light.intensity = ft_atod(split[1]);
	if (!set_color(color, &ambiant_light.color) || ambiant_light.intensity < 0
		|| ambiant_light.intensity > 1)
	{
		string_array_free(split);
		print_error_msg("invalid ambiant light param");
	}
	rt->scene.ambiant_light = ambiant_light;
}

void	set_camera(char **split, t_rt *rt)
{
	char		**coord;
	char		**direction;
	t_camera	camera;

	if (!split[1] || !split[2] || !split[3] || split[4])
	{
		string_array_free(split);
		print_error_msg("invalid camera format");
	}
	coord = ft_split(split[1], ",");
	direction = ft_split(split[2], ",");
	camera.fov = ft_atod(split[3]);
	if (!set_coord(coord, &camera.position) || !set_coord(direction, &camera.direction)
		|| !correct_direction(camera.direction) || camera.fov < 0 || camera.fov > 180)
	{
		string_array_free(split);
		print_error_msg("invalid camera parameter");
	}
	ft_lstadd_front(&rt->scene.camera, ft_lstnew(&camera));
}


void	set_light(char **split, t_rt *rt)
{
	char		**coord;
	char		**color;
	t_light		light;

	if (!split[1] || !split[2] || !split[3] || split[4])
	{
		string_array_free(split);
		print_error_msg("invalid light format");
	}
	coord = ft_split(split[1], ",");
	color = ft_split(split[3], ",");
	light.intensity = ft_atod(split[2]);
	if (!set_coord(coord, &light.position) || !set_color(color, &light.color)
		|| light.intensity < 0 || light.intensity > 1)
	{
		string_array_free(split);
		print_error_msg("invalid light parameters");
	}
	ft_lstadd_front(&rt->scene.light, ft_lstnew(&light));
}
