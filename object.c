/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:11:56 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 20:20:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		free_object(void *obj)
{
	t_object	*object;

	if (obj)
	{
		object = (t_object *)obj;
		if (object->ptr)
			free(object->ptr);
		if (object->vertex)
			free(object->vertex);
		free(object);
	}
}

int			set_vertices(t_object *object, char **split)
{
	int		i;
	char	**coord;

	object->vertex = malloc(sizeof(*(object->vertex)) * object->nvertices);
	if (!object->vertex)
		return (0);
	i = 0;
	while (i < object->nvertices)
	{
		coord = ft_split(split[i + 1], ",");
		if (!set_coord(coord, &object->vertex[i]))
			return (0);
		i++;
	}
	return (1);
}

int			set_direction(t_object *object, char **split)
{
	int		check_dir;
	char	**coord;

	if (object->rotate)
	{
		coord = ft_split(split[1 + object->nvertices], ",");
		check_dir = set_coord(coord, &object->current_direction);
		if (!check_dir || !correct_direction(object->current_direction))
			return (0);
	}
	return (1);
}

t_object	*set_reflexion(t_object *object, char **split, int i)
{
	double	atod;

	object->reflective = 0;
	object->specular = -1;
	if (split[i])
	{
		atod = ft_atod(split[i]);
		if (!isnan(atod) && atod > 0)
			object->specular = MAX(0.0, MIN(10000.0, atod));
		if (split[i + 1])
		{
			atod = ft_atod(split[i + 1]);
			if (!isnan(atod) && atod > 0)
				object->reflective = MAX(0.0, MIN(1.0, atod));
		}
	}
	return (object);
}

t_object	*new_object(char **split,
						int color_index,
						int nvertices,
						int rotate)
{
	t_object	*obj;
	char		**color;

	obj = malloc(sizeof(*obj));
	if (!obj)
		return (NULL);
	obj->rotate = rotate;
	obj->ptr = NULL;
	obj->vertex = NULL;
	obj->nvertices = nvertices;
	color = ft_split(split[color_index], ",");
	if (!set_color(color, &obj->color)
		|| !set_vertices(obj, split)
		|| !set_direction(obj, split))
	{
		free_object(obj);
		return (NULL);
	}
	obj = set_reflexion(obj, split, color_index + 1);
	init_rotation_matrix(obj->to_world_matrix);
	return (obj);
}
