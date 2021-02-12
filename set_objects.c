/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:37:37 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 08:13:37 by user42           ###   ########.fr       */
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
	if (!sphere || !object || !split[1] || !split[2] || !split[3] || split[4])
		return (0);
	coord = ft_split(split[1], ",");
	color = ft_split(split[3], ",");
	sphere->diameter = ft_atod(split[2]);
	if (!set_coord(coord, &object->position) || !set_color(color, &object->color) || 
		sphere->diameter <= 0)
		return (0);
	set_object(object, sphere, 0, 500);
	object->reflective = 0;
	object->direction = new_vector(0, 0, 0);
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
	//t_plane		*plane;
	t_object	*object;

	//plane = malloc(sizeof(*plane));
	// if (!plane)
	object = malloc(sizeof(*object));
	if (!object || !split[1] || !split[2] || !split[3] || split[4])
		return (0);
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[3], ",");
	if (!set_coord(coord, &object->position) || !set_coord(dir, &object->direction) ||
		!set_color(color, &object->color) || !correct_direction(object->direction))
		return (0);
	set_object(object, NULL, 1, -1);
	object->reflective = 0;
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
	if (!square || !object || !split[1] || !split[2] || !split[3] || !split[4] || split[5])
		return (0);
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[4], ",");
	square->height = ft_atod(split[3]);
	if (!set_coord(coord, &object->position) || !set_coord(dir, &object->direction) ||
		!set_color(color, &object->color) || !correct_direction(object->direction)
		|| square->height <= 0)
		return (0);
	set_object(object, square, 1, 0);
	object->reflective = 0;
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
	if (!cylinder || !object 
		|| !split[1] || !split[2] || !split[3] || !split[4] || !split[5] || split[6])
		return (0);
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[5], ",");
	cylinder->diameter = ft_atod(split[3]);
	cylinder->height = ft_atod(split[4]);
	if (!set_coord(coord, &object->position) || !set_coord(dir, &object->direction)
		|| !set_color(color, &object->color) || !correct_direction(object->direction)
		|| cylinder->diameter <= 0 || cylinder->height <= 0)
		return (0);
	set_object(object, cylinder, 1, 2000);
	object->reflective = 0;
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
	t_triangle	*triangle;
	t_object	*object;

	triangle = malloc(sizeof(*triangle));
	object = malloc(sizeof(*object));
	if (!triangle || !object || !split[1] || !split[2] || !split[3] || !split[4] || split[5])
		return (0);
	coord[0] = ft_split(split[1], ",");
	coord[1] = ft_split(split[2], ",");
	coord[2] = ft_split(split[3], ",");
	color = ft_split(split[4], ",");
	if (!set_coord(coord[0], &triangle->p0) || !set_coord(coord[1], &triangle->p1)
		|| !set_coord(coord[2], &triangle->p2) || !set_color(color, &object->color))
		return (0);
	set_object(object, triangle, 0, 1000);
	object->reflective = 0;
	object->intersect = &ray_triangle_intersect;
	object->get_normal = &get_triangle_normal;
	object->current_direction = new_vector(0, 0, 0);
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}
