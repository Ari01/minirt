/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:37:37 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 18:44:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_sphere(char **split, t_rt *rt)
{
	t_sphere	*sphere;
	t_object	*object;

	if (ft_streq(split[0], "sp"))
	{
		sphere = malloc(sizeof(*sphere));
		if (!check_nargs(split, 3) || !sphere)
			return (0);
		if (!(object = new_object(split, 3, 1, 0)))
		{
			free(sphere);
			return (0);
		}
		sphere->diameter = ft_atod(split[2]);
		object->ptr = sphere;
		if (!check_object_param(object, sphere->diameter))
			return (0);
		object->intersect = &ray_sphere_intersect;
		object->get_normal = &get_sphere_normal;
		ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
		return (1);
	}
	return (0);
}

int		set_plane(char **split, t_rt *rt)
{
	t_object	*object;

	if (ft_streq(split[0], "pl"))
	{
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
	return (0);
}

int		set_square(char **split, t_rt *rt)
{
	t_square	*square;
	t_object	*object;

	if (ft_streq(split[0], "sq"))
	{
		square = malloc(sizeof(*square));
		if (!check_nargs(split, 4) || !square)
			return (0);
		object = new_object(split, 4, 1, 1);
		if (!object)
		{
			free(square);
			return (0);
		}
		square->height = ft_atod(split[3]);
		object->ptr = square;
		if (!check_object_param(object, square->height))
			return (0);
		object->intersect = &ray_square_intersect;
		object->get_normal = &get_plane_normal;
		ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
		return (1);
	}
	return (0);
}

int		set_cylinder(char **split, t_rt *rt)
{
	t_cylinder	*cylinder;
	t_object	*object;

	if (ft_streq(split[0], "cy"))
	{
		cylinder = malloc(sizeof(*cylinder));
		if (!check_nargs(split, 5) || !cylinder)
			return (0);
		if (!(object = new_object(split, 5, 1, 1)))
		{
			free(cylinder);
			return (0);
		}
		cylinder->diameter = ft_atod(split[3]);
		cylinder->height = ft_atod(split[4]);
		object->ptr = cylinder;
		if (!check_object_param(object, cylinder->diameter)
			|| !check_object_param(object, cylinder->height))
			return (0);
		object->intersect = &ray_cylinder_intersect;
		object->get_normal = &get_cylinder_normal;
		ft_lstadd_front(&rt->scene.objects, ft_lstnew(object));
		return (1);
	}
	return (0);
}

int		set_triangle(char **split, t_rt *rt)
{
	t_object	*object;

	if (ft_streq(split[0], "tr"))
	{
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
	return (0);
}
