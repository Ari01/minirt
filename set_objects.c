/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:37:37 by user42            #+#    #+#             */
/*   Updated: 2021/02/22 21:31:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_nargs(char **split, int nargs)
{
	int	i;

	i = 1;
	while (i <= nargs)
	{
		if (!split[i])
			return (0);
		i++;
	}
	return (1);
}

int		set_sphere(char **split, t_rt *rt)
{
	t_sphere	*sphere;
	t_object	*object;

	if (!check_nargs(split, 3))
		return (0);
	sphere = malloc(sizeof(*sphere));
	object = new_object(split, 3, 1, 0);
	if (!sphere || !object)
		return (0);
	sphere->diameter = ft_atod(split[2]);
	if (sphere->diameter <= 0)
	{
		free(object);
		free(sphere);
		return (0);
	}
	object->ptr = sphere;
	object->intersect = &ray_sphere_intersect;
	object->get_normal = &get_sphere_normal;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_plane(char **split, t_rt *rt)
{
	t_object	*object;

	if (!check_nargs(split, 3))
		return (0);
	object = new_object(split, 3, 1, 1);
	if (!object)
		return (0);
	object->intersect = &ray_plane_intersect;
	object->get_normal = &get_plane_normal;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_square(char **split, t_rt *rt)
{
	t_square	*square;
	t_object	*object;

	if (!check_nargs(split, 4))
		return (0);
	square = malloc(sizeof(*square));
	object = new_object(split, 4, 1, 1);
	if (!square || !object)
		return (0);
	square->height = ft_atod(split[3]);
	if (square->height <= 0)
	{
		free(square);
		free(object);
		return (0);
	}
	object->ptr = square;
	object->intersect = &ray_square_intersect;
	object->get_normal = &get_plane_normal;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_cylinder(char **split, t_rt *rt)
{
	t_cylinder	*cylinder;
	t_object	*object;

	if (!check_nargs(split, 5))
		return (0);
	cylinder = malloc(sizeof(*cylinder));
	object = new_object(split, 5, 1, 1);
	if (!cylinder || !object)
		return (0);
	cylinder->diameter = ft_atod(split[3]);
	cylinder->height = ft_atod(split[4]);
	if (cylinder->diameter <= 0 || cylinder->height <= 0)
	{
		free(cylinder);
		free(object);
		return (0);
	}
	object->ptr = cylinder;
	object->intersect = &ray_cylinder_intersect;
	object->get_normal = &get_cylinder_normal;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}

int	set_triangle(char **split, t_rt *rt)
{
	t_object	*object;

	if (!check_nargs(split, 4))
		return (0);
	object = new_object(split, 4, 3, 0);
	if (!object)
		return (0);
	object->intersect = &ray_triangle_intersect;
	object->get_normal = &get_triangle_normal;
	ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
	return (1);
}
