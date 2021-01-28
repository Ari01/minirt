/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:11:56 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 13:49:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_object(t_object *object, void *ptr, int rotate, double specular)
{
	object->ptr = ptr;
	object->specular = specular;
	object->rotate = rotate;
	init_rotation_matrix(object->to_world_matrix);
	object->to_world_matrix[3] = object->position;
}
