/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:11:56 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 20:46:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_object_matrix(t_object *object)
{
	t_vector	right;
	t_vector	up;

	init_rotation_matrix(object->to_world_matrix);
	if (object->direction.x || object->direction.y || object->direction.z)
	{
		right = vector_cross(new_vector(0, 0, 1), object->direction);
		up = vector_cross(object->direction, right);
		object->to_world_matrix[0] = right;
		object->to_world_matrix[1] = up;
		object->to_world_matrix[2] = object->direction;
	}
	object->to_world_matrix[3] = new_vector(object->position.x, 
											object->position.y, 
											object->position.z);
}
