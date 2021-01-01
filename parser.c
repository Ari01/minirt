/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:00:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/01 10:51:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	string_array_free(char **split)
{
	int i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
		split = NULL;
	}
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
	int valid_format;

	valid_format = 1;
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		valid_format = 0;
	else
	{
		*color = new_color(ft_atod(split[0]), ft_atod(split[1]), ft_atod(split[2]));
		if (color->r < 0 || color->r > 255
			|| color->g < 0 || color->g > 255
			|| color->b < 0 || color->b > 255)
			valid_format = 0;
	}
	string_array_free(split);
	return (valid_format);
}

int		set_coord(char **split, t_vector *coord)
{
	int	valid_format;

	valid_format = 1;
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		valid_format = 0;
	else
		*coord = new_vector(ft_atod(split[0]), ft_atod(split[1]), ft_atod(split[2]));
	string_array_free(split);
	return (valid_format);
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
		print_error_msg("invalid ambiant light intensity");
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
	printf("direction = %s %s %s\n", direction[0], direction[1], direction[2]);
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

void	set_sphere(char **split, t_rt *rt)
{
	char		**coord;
	char		**color;
	t_sphere	sphere;

	if (!split[1] || !split[2] || !split[3] || split[4])
	{
		string_array_free(split);
		print_error_msg("invalid sphere format");
	}
	coord = ft_split(split[1], ",");
	color = ft_split(split[3], ",");
	sphere.diameter = ft_atod(split[2]);
	if (!set_coord(coord, &sphere.center) || !set_color(color, &sphere.color) || 
		sphere.diameter <= 0)
	{
		string_array_free(split);
		print_error_msg("invalid sphere parameters");
	}
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(&sphere));
}

void	set_plane(char **split, t_rt *rt)
{
	char		**coord;
	char		**dir;
	char		**color;
	t_plane		plane;

	if (!split[1] || !split[2] || !split[3] || split[4])
	{
		string_array_free(split);
		print_error_msg("invalid plane format");
	}
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[3], ",");
	if (!set_coord(coord, &plane.position) || !set_coord(dir, &plane.direction) ||
		!set_color(color, &plane.color) || !correct_direction(plane.direction))
	{
		string_array_free(split);
		print_error_msg("invalid plane parameters");
	}
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(&plane));
}

void	set_square(char **split, t_rt *rt)
{
	char		**coord;
	char		**dir;
	char		**color;
	t_square	square;

	if (!split[1] || !split[2] || !split[3] || split[4])
	{
		string_array_free(split);
		print_error_msg("invalid plane format");
	}
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[3], ",");
	if (!set_coord(coord, &plane.position) || !set_coord(dir, &plane.direction) ||
		!set_color(color, &plane.color) || !correct_direction(plane.direction))
	{
		string_array_free(split);
		print_error_msg("invalid plane parameters");
	}
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(&plane));
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
			if (!ft_strncmp(split[0], "sp", id_len))
			{
				set_sphere(split, &rt);
				t_sphere sphere;
				sphere = *(t_sphere*)rt.scene.objects->content;
				printf("sphere coord = %f %f %f, diameter = %f, color = %f %f %f\n", sphere.center.x, sphere.center.y, sphere.center.z, sphere.diameter, sphere.color.r, sphere.color.g, sphere.color.b);
			}
			if (!ft_strncmp(split[0], "pl", id_len))
			{
				set_plane(split, &rt);
				t_plane plane;
				plane = *(t_plane*)rt.scene.objects->content;
				printf("plane coord = %f %f %f, direction = %f %f %f, color = %f %f %f\n", plane.position.x, plane.position.y, plane.position.z, plane.direction.x, plane.direction.y, plane.direction.z, plane.color.r, plane.color.g, plane.color.b);
			}
			if (!ft_strncmp(split[0], "sq", id_len))
			{
				set_square(split, &rt);
			}
			if (!ft_strncmp(split[0], "cy", id_len))
			{
				set_cylindre(split, &rt);
			}
			if (!ft_strncmp(split[0], "tr", id_len))
			{
				set_triangle(split, &rt);
			}
			string_array_free(split);
			free(line);
			split = NULL;
			line = NULL;
		}
	}
	//check_missing_parameters(&rt);
	return (rt);
}
