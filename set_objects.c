/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:37:37 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 17:10:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_sphere(char **split, t_rt *rt)
{
	char		**coord;
	char		**color;
	t_sphere	*sphere;
	t_object	*object;

	sphere = malloc(sizeof(*sphere));
	object = malloc(sizeof(*object));
	object->vertex = malloc(sizeof(*(object->vertex)));
	if (!sphere || !object || !object->vertex || !split[1] || !split[2] || !split[3])
		return (0);
	coord = ft_split(split[1], ",");
	color = ft_split(split[3], ",");
	sphere->diameter = ft_atod(split[2]);
	if (!set_coord(coord, object->vertex) || !set_color(color, &object->color) || 
		sphere->diameter <= 0)
		return (0);
	set_object(object, sphere, 0, -1);
	object->reflective = 0;
	if (split[4])
	{
		object->specular = MAX(0.0, MIN(10000.0, (ft_atod(split[4]))));
		if (split[5])
			object->reflective = MAX(0.0, MIN(1.0, ft_atod(split[5])));
	}
	object->nvertices = 1;
	object->intersect = &ray_sphere_intersect;
	object->get_normal = &get_sphere_normal;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_plane(char **split, t_rt *rt)
{
	char		**coord;
	char		**dir;
	char		**color;
	t_object	*object;

	object = malloc(sizeof(*object));
	object->vertex = malloc(sizeof(*(object->vertex)));
	if (!object || !object->vertex || !split[1] || !split[2] || !split[3])
		return (0);
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[3], ",");
	if (!set_coord(coord, object->vertex) || !set_coord(dir, &object->direction) ||
		!set_color(color, &object->color) || !correct_direction(object->direction))
		return (0);
	set_object(object, NULL, 1, -1);
	object->reflective = 0;
	if (split[4])
	{
		object->specular = MAX(0.0, MIN(5000.0, (ft_atod(split[4]))));
		if (split[5])
			object->reflective = MAX(0.0, MIN(1.0, ft_atod(split[5])));
	}
	object->nvertices = 1;
	object->intersect = &ray_plane_intersect;
	object->get_normal = &get_plane_normal;
	object->current_direction = object->direction;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_square(char **split, t_rt *rt)
{
	char		**coord;
	char		**dir;
	char		**color;
	t_square	*square;
	t_object	*object;

	square = malloc(sizeof(*square));
	object = malloc(sizeof(*object));
	object->vertex = malloc(sizeof(*(object->vertex)));
	if (!square || !object || !object->vertex 
		|| !split[1] || !split[2] || !split[3] || !split[4])
		return (0);
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[4], ",");
	square->height = ft_atod(split[3]);
	if (!set_coord(coord, object->vertex) || !set_coord(dir, &object->direction) ||
		!set_color(color, &object->color) || !correct_direction(object->direction)
		|| square->height <= 0)
		return (0);
	set_object(object, square, 1, -1);
	object->reflective = 0;
	if (split[5])
	{
		object->specular = MAX(0.0, MIN(5000.0, (ft_atod(split[5]))));
		if (split[6])
			object->reflective = MAX(0.0, MIN(1.0, ft_atod(split[6])));
	}
	object->nvertices = 1;
	object->intersect = &ray_square_intersect;
	object->get_normal = &get_plane_normal;
	object->current_direction = object->direction;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_cylinder(char **split, t_rt *rt)
{
	char		**coord;
	char		**dir;
	char		**color;
	t_cylinder	*cylinder;
	t_object	*object;

	cylinder = malloc(sizeof(*cylinder));
	object = malloc(sizeof(*object));
	object->vertex = malloc(sizeof(*(object->vertex)));
	if (!cylinder || !object || !object->vertex 
		|| !split[1] || !split[2] || !split[3] || !split[4] || !split[5])
		return (0);
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[5], ",");
	cylinder->diameter = ft_atod(split[3]);
	cylinder->height = ft_atod(split[4]);
	if (!set_coord(coord, object->vertex) || !set_coord(dir, &object->direction)
		|| !set_color(color, &object->color) || !correct_direction(object->direction)
		|| cylinder->diameter <= 0 || cylinder->height <= 0)
		return (0);
	set_object(object, cylinder, 1, -1);
	object->reflective = 0;
	if (split[6])
	{
		object->specular = MAX(0.0, MIN(5000.0, (ft_atod(split[6]))));
		if (split[7])
			object->reflective = MAX(0.0, MIN(1.0, ft_atod(split[7])));
	}
	object->nvertices = 1;
	object->intersect = &ray_cylinder_intersect;
	object->get_normal = &get_cylinder_normal;
	object->current_direction = object->direction;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_triangle(char **split, t_rt *rt)
{
	char		**coord[3];
	char		**color;
	t_object	*object;

	object = malloc(sizeof(*object));
	object->vertex = malloc(sizeof(*(object->vertex)) * 3);
	object->vertex[0] = new_vector(0,0,0);
	object->vertex[1] = new_vector(0,0,0);
	object->vertex[2] = new_vector(0,0,0);
	if (!object || !object->vertex || !split[1] 
		|| !split[2] || !split[3] || !split[4])
		return (0);
	coord[0] = ft_split(split[1], ",");
	coord[1] = ft_split(split[2], ",");
	coord[2] = ft_split(split[3], ",");
	color = ft_split(split[4], ",");
	if (!set_coord(coord[0], &object->vertex[0]) || !set_coord(coord[1], &object->vertex[1])
		|| !set_coord(coord[2], &object->vertex[2]) || !set_color(color, &object->color))
		return (0);
	set_object(object, NULL, 0, -1);
	object->reflective = 0;
	if (split[5])
	{
		object->specular = MAX(0.0, MIN(5000.0, (ft_atod(split[5]))));
		if (split[6])
			object->reflective = MAX(0.0, MIN(1.0, ft_atod(split[6])));
	}
	object->nvertices = 3;
	object->intersect = &ray_triangle_intersect;
	object->get_normal = &get_triangle_normal;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}
