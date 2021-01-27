/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:44:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 15:15:04 by user42           ###   ########.fr       */
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
		set_camera_matrix(camera);
/*	int i = 0;
	while (i < 4)
	{
		printf("cam to world\n %f %f %f\n", camera->to_world_matrix[i].x, camera->to_world_matrix[i].y, camera->to_world_matrix[i].z);
		i++;
	}*/
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

int		set_scene(char *line, char **split, t_rt *rt)
{
	int		valid_scene;

	valid_scene = 1;
	split = ft_split(line, " \t");
	if (!split || !*split || !ft_strnstr(ELEM_ID_SET, split[0], 1024))
		valid_scene = 0;
	else if (!ft_strncmp(split[0], "R", 2))
		valid_scene = set_resolution(split, rt);
	else if (!ft_strncmp(split[0], "A", 2))
		valid_scene = set_ambiant_light(split, rt);
	else if (!ft_strncmp(split[0], "c", 2))
		valid_scene = set_camera(split, rt);
	else if (!ft_strncmp(split[0], "l", 2))
		valid_scene = set_light(split, rt);
	else if (!ft_strncmp(split[0], "sp", 2))
		valid_scene = set_sphere(split, rt);
	else if (!ft_strncmp(split[0], "pl", 2))
		valid_scene = set_plane(split, rt);
	else if (!ft_strncmp(split[0], "sq", 2))
		valid_scene = set_square(split, rt);
	else if (!ft_strncmp(split[0], "cy", 2))
		valid_scene = set_cylindre(split, rt);
	else if (!ft_strncmp(split[0], "tr", 2))
		valid_scene = set_triangle(split, rt);
	string_array_free(split);
	return (valid_scene);
}

