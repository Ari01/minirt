/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:37:37 by user42            #+#    #+#             */
/*   Updated: 2021/01/02 14:26:23 by user42           ###   ########.fr       */
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
	if (!set_coord(coord, &sphere->center) || !set_color(color, &sphere->color) || 
		sphere->diameter <= 0)
		return (0);
	object->ptr = sphere;
	object->intersect = NULL;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_plane(char **split, t_rt *rt)
{
	char		**coord;
	char		**dir;
	char		**color;
	t_plane		*plane;
	t_object	*object;

	plane = malloc(sizeof(*plane));
	object = malloc(sizeof(*object));
	if (!plane || !object || !split[1] || !split[2] || !split[3] || split[4])
		return (0);
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[3], ",");
	if (!set_coord(coord, &plane->position) || !set_coord(dir, &plane->direction) ||
		!set_color(color, &plane->color) || !correct_direction(plane->direction))
		return (0);
	object->ptr = plane;
	object->intersect = NULL;
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
	if (!set_coord(coord, &square->position) || !set_coord(dir, &square->direction) ||
		!set_color(color, &square->color) || !correct_direction(square->direction)
		|| square->height <= 0)
		return (0);
	object->ptr = square;
	object->intersect = NULL;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_cylindre(char **split, t_rt *rt)
{
	char		**coord;
	char		**dir;
	char		**color;
	t_cylindre	*cylindre;
	t_object	*object;

	cylindre = malloc(sizeof(*cylindre));
	object = malloc(sizeof(*object));
	if (!cylindre || !object 
		|| !split[1] || !split[2] || !split[3] || !split[4] || !split[5] || split[6])
		return (0);
	coord = ft_split(split[1], ",");
	dir = ft_split(split[2], ",");
	color = ft_split(split[5], ",");
	cylindre->diameter = ft_atod(split[3]);
	cylindre->height = ft_atod(split[4]);
	if (!set_coord(coord, &cylindre->position) || !set_coord(dir, &cylindre->direction)
		|| !set_color(color, &cylindre->color) || !correct_direction(cylindre->direction)
		|| cylindre->diameter <= 0 || cylindre->height <= 0)
		return (0);
	object->ptr = cylindre;
	object->intersect = NULL;
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
	if (!set_coord(coord[0], &triangle->p1) || !set_coord(coord[1], &triangle->p2)
		|| !set_coord(coord[2], &triangle->p3) || !set_color(color, &triangle->color))
		return (0);
	object->ptr = triangle;
	object->intersect = NULL;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}
