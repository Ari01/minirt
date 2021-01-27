/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:11:56 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 16:50:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_object_matrix(t_list *objects, t_vector *cam_matrix)
{
	t_list		*ite;
	t_object	*current_obj;

	ite = objects;

		(void)cam_matrix;
	while (ite)
	{
		current_obj = (t_object *)ite->content;
		init_rotation_matrix(current_obj->to_world_matrix);
	//	matrix_mul(current_obj->to_world_matrix, cam_matrix);
		ite = ite->next;
	}
}

void	set_object_matrix(t_list *objects, t_vector *cam_matrix)
{
	t_list		*ite;
	t_object	*current_obj;

	ite = objects;
	while (ite)
	{
		current_obj = (t_object *)ite->content;
		matrix_mul(current_obj->to_world_matrix, cam_matrix);
		ite = ite->next;
	}
}
