/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:44:14 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 19:46:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_resolution(char **split, t_rt *rt)
{
	if (!ft_strncmp(split[0], "R", 2))
	{
		if (rt->width != -1 || rt->height != -1
			|| !split[1] || !split[2] || split[3])
			return (0);
		rt->width = ft_atod(split[1]);
		rt->height = ft_atod(split[2]);
		if (rt->width > 0 && rt->height > 0)
			return (1);
	}
	return (0);
}

int		set_ambiant_light(char **split, t_rt *rt)
{
	char			**color;
	t_ambiant_light	ambiant_light;

	if (!ft_strncmp(split[0], "A", 2))
	{
		if (rt->scene.ambiant_light.intensity != -1
			|| !split[1] || !split[2] || split[3])
			return (0);
		color = ft_split(split[2], ",");
		ambiant_light.intensity = ft_atod(split[1]);
		if (set_color(color, &ambiant_light.color)
			&& ambiant_light.intensity > 0.0
			&& ambiant_light.intensity <= 1.0)
		{
			rt->scene.ambiant_light = ambiant_light;
			return (1);
		}
	}
	return (0);
}

int		set_camera(char **split, t_rt *rt)
{
	char		**coord;
	char		**direction;
	t_camera	*camera;

	if (!ft_strncmp(split[0], "c", 2))
	{
		if (!(camera = malloc(sizeof(*camera))))
			return (0);
		if (check_nargs(split, 3))
		{
			coord = ft_split(split[1], ",");
			direction = ft_split(split[2], ",");
			camera->fov = ft_atod(split[3]);
			if (set_coord(coord, &camera->position)
				&& set_coord(direction, &camera->direction)
				&& correct_direction(camera->direction)
				&& camera->fov > 0 && camera->fov <= 180)
			{
				add_camera(rt, camera);	
				return (1);
			}
		}
		free(camera);
	}
	return (0);
}

int		set_light(char **split, t_rt *rt)
{
	char		**coord;
	char		**color;
	t_light		*light;

	if (!ft_strncmp(split[0], "l", 2))
	{
		if (!(light = malloc(sizeof(*light))))
			return (0);
		if (check_nargs(split, 3))
		{
			coord = ft_split(split[1], ",");
			color = ft_split(split[3], ",");
			light->intensity = ft_atod(split[2]);
			if (set_coord(coord, &light->position) && set_color(color, &light->color)
				&& light->intensity >= 0 && light->intensity <= 1)
			{
				ft_lstadd_front(&rt->scene.light, ft_lstnew(light));
				return (1);
			}
		}
		free(light);
	}
	return (0);
}

int		set_scene(char *line, t_rt *rt)
{
	int		valid_scene;
	char	**split;

	valid_scene = 0;
	split = ft_split(line, " \t");
	if (!split || !(*split))
	{
		string_array_free(split);
		return (0);
	}
	if (set_resolution(split, rt)
		|| set_ambiant_light(split, rt)
		|| set_camera(split, rt)
		|| set_light(split, rt)
		|| set_sphere(split, rt)
		|| set_plane(split, rt)
		|| set_square(split, rt)
		|| set_cylinder(split, rt)
		|| set_triangle(split, rt))
		valid_scene = 1;
	string_array_free(split);
	return (valid_scene);
}
