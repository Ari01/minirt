/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:11:56 by user42            #+#    #+#             */
/*   Updated: 2021/02/22 21:34:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		{
			free(object->vertex);
			return (0);
		}
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
	object->reflective = 0;
	object->specular = -1;
	if (split[i])
	{
		object->specular = MAX(0.0, MIN(10000.0, (ft_atod(split[i]))));
		if (split[i + 1])
			object->reflective = MAX(0.0, MIN(1.0, ft_atod(split[i + 1])));
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
	obj->ptr = NULL;
	obj->rotate = rotate;
	obj->nvertices = nvertices;
	color = ft_split(split[color_index], ",");
	if (!set_vertices(obj, split) || !set_direction(obj, split)
		|| !set_color(color, &obj->color))
	{
		free(obj);
		return (NULL);
	}
	obj = set_reflexion(obj, split, color_index + 1);
	init_rotation_matrix(obj->to_world_matrix);
	return (obj);
}
