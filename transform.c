/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:28:39 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 22:02:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		move_object(int key, t_vector *matrix, t_vector *cam_matrix)
{
	t_vector	v;

	if (key == 'q')
		v = new_vector(-1, 0, 0);
	if (key == 'd')
		v = new_vector(1, 0, 0);
	if (key == 'z')
		v = new_vector(0, 0, 1);
	if (key == 's')
		v = new_vector(0, 0, -1);
	if (key == SPACE)
		v = new_vector(0, 1, 0);
	if (key == CONTROL)
		v = new_vector(0, -1, 0);
	v = dir_matrix_mul(v, cam_matrix);
	v.x += matrix[3].x;
	v.y += matrix[3].y;
	v.z += matrix[3].z;
	matrix[3] = v;
}

void		rotate_object(int key, t_vector *matrix)
{
	double		xdeg = 0;
	double		ydeg = 0;
	t_vector	mtmp[3];

	init_rotation_matrix(mtmp);
	if (key == 'q' || key == 'd')
	{
		xdeg += (key == 'q' ? -10 : 10);
		set_yrotation_matrix(mtmp, xdeg);
		matrix_mul(matrix, mtmp);
	}
	if (key == 'z' || key == 's')
	{
		ydeg += (key == 'z' ? -10 : 10);
		set_xrotation_matrix(mtmp, ydeg);
		matrix_mul(matrix, mtmp);
	}
}
