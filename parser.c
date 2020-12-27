/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:00:51 by user42            #+#    #+#             */
/*   Updated: 2020/12/27 12:04:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	string_array_free(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}

void	check_missing_parameters(t_rt *rt)
{
	if (rt->width <= 0 || rt->height <= 0)
		print_error_msg("missing resolution");
	if (rt->scene.ambiant_light.intensity <= 0)
		print_error_msg("missing ambiant light");
	if (!rt->scene.camera)
		print_error_msg("missing camera");
	if (!rt->scene.objects)
		print_error_msg("missing object");
}

int		set_color(char **split, t_color *color)
{
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (0);
	*color = new_color(ft_atod(split[0]), ft_atod(split[1]), ft_atod(split[2]));
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (0);
	return (1);
}

int		set_coord(char **split, t_vector *coord)
{
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (0);
	*coord = new_vector(ft_atod(split[0]), ft_atod(split[1]), ft_atod(split[2]));
	return (1);
}

int		correct_direction(t_vector dir)
{
	if (dir.x < -1 || dir.x > 1
		|| dir.y < -1 || dir.y > 1
		|| dir.z < -1 || dir.z > 1)
		return (0);
	return (1);
}

void	set_resolution(char **split, t_rt *rt)
{
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
	char **tmp;

	if (!split[1] || !split[2] || split[3])
		print_error_msg("invalid ambiant light format");
	tmp = ft_split(split[2], ",");
	if (!set_color(tmp, &rt->scene.ambiant_light.color))
	{
		string_array_free(tmp);
		string_array_free(split);
		print_error_msg("invalid ambiant light color");
	}
	free(tmp);
	rt->scene.ambiant_light.intensity = ft_atod(split[1]);
	if (rt->scene.ambiant_light.intensity < 0
		|| rt->scene.ambiant_light.intensity > 1)
	{
		string_array_free(split);
		print_error_msg("invalid ambiant light intensity");
	}
}

void	set_camera(char **split, t_rt *rt)
{
	char		**coord;
	char		**direction;
	t_camera	camera;
	int			invalid_coord;

	invalid_coord = 0;
	if (!split[1] || !split[2] || !split[3] || split[4])
	{
		string_array_free(split);
		print_error_msg("invalid camera format");
	}
	coord = ft_split(split[1], ",");
	direction = ft_split(split[2], ",");
	if (!set_coord(coord, &camera.position) || !set_coord(direction, &camera.direction)
		|| !correct_direction(camera.direction))
		invalid_coord = 1;
	string_array_free(coord);
	string_array_free(direction);
	camera.fov = ft_atod(split[3]);
	if (invalid_coord || camera.fov < 0 || camera.fov > 180)
	{
		string_array_free(split);
		print_error_msg("invalid camera fov");
	}
	ft_lstadd_front(&rt->scene.camera, ft_lstnew(&camera));
}

void	set_light(char **split, t_rt *rt)
{
	char		**coord;
	char		**color;
	t_light		light;
	int			invalid_param;

	invalid_param = 0;
	if (!split[1] || !split[2] || !split[3] || split[4])
	{
		string_array_free(split);
		print_error_msg("invalid light format");
	}
	coord = ft_split(split[1], ",");
	color = ft_split(split[3], ",");
	if (!set_coord(coord, &light.position) || !set_color(color, &light.color))
		invalid_param = 1;
	string_array_free(coord);
	string_array_free(color);
	light.intensity = ft_atod(split[2]);
	if (invalid_param || light.intensity < 0 || light.intensity > 1)
	{
		string_array_free(split);
		print_error_msg("invalid light parameters");
	}
	ft_lstadd_front(&rt->scene.light, ft_lstnew(&light));
}

t_rt	parse(char *pathfile)
{
	t_rt	rt;
	int		fd;
	size_t	id_len;
	char	*line;
	char	**split;

	fd = open(pathfile, O_RDONLY);
	if (fd == -1)
		perror(strerror(errno));
	line = NULL;
	rt = init_rt();
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
		{
			split = ft_split(line, " \t");
			id_len = ft_strlen(split[0]);
			printf("split 0 = %s\n", split[0]);
			if (!split || !*split)
				print_error_msg("couldn't read line");
			if (!ft_strnstr(ELEM_ID_SET, split[0], 1024))
				print_error_msg("invalid element id");
			if (!ft_strncmp(split[0], "R", id_len))
			{
				set_resolution(split, &rt);
				printf("res = %f %f\n", rt.width, rt.height);
			}
			if (!ft_strncmp(split[0], "A", id_len))
			{
				set_ambiant_light(split, &rt);
				printf("ambiant light intensity = %f, color = %f %f %f\n", rt.scene.ambiant_light.intensity, rt.scene.ambiant_light.color.r, rt.scene.ambiant_light.color.g, rt.scene.ambiant_light.color.b);
			}
			if (!ft_strncmp(split[0], "c", id_len))
			{
				printf("sp0 = %s\n", split[0]);
				set_camera(split, &rt);
				t_camera cam;
				cam = *(t_camera*)rt.scene.camera->content;
				printf("cam coord = %f %f %f, dir = %f %f %f, fov = %f\n", cam.position.x, cam.position.y, cam.position.z, cam.direction.x, cam.direction.y, cam.direction.z, cam.fov);
			}
			if (!ft_strncmp(split[0], "l", id_len))
			{
				set_light(split, &rt);
				t_light light;
				light = *(t_light*)rt.scene.light->content;
				printf("light coord = %f %f %f, intensity = %f, color = %f %f %f\n", light.position.x, light.position.y, light.position.z, light.intensity, light.color.r, light.color.g, light.color.b);
			}
			/*if (**line == 's' && **(line + 1) == 'p')
				set_sphere(split, &rt);*/
			string_array_free(split);
			free(line);
			split = NULL;
			line = NULL;
		}
	}
	//check_missing_parameters(&rt);
	return (rt);
}
