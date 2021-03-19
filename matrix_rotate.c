/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:47:52 by user42            #+#    #+#             */
/*   Updated: 2021/03/19 08:44:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_rotation_matrix(t_vector *m)
{
	m[0] = new_vector(1, 0, 0);
	m[1] = new_vector(0, 1, 0);
	m[2] = new_vector(0, 0, 1);
}

void		set_xrotation_matrix(t_vector *m, double angle)
{
	angle *= M_PI / 180;
	m[1].y = cos(angle);
	m[1].z = sin(angle);
	m[2].y = -sin(angle);
	m[2].z = cos(angle);
}

void		set_yrotation_matrix(t_vector *m, double angle)
{
	angle *= M_PI / 180;
	m[0].x = cos(angle);
	m[0].z = -sin(angle);
	m[2].x = sin(angle);
	m[2].z = cos(angle);
}

void		set_zrotation_matrix(t_vector *m, double angle)
{
	angle *= M_PI / 180;
	m[0].x = cos(angle);
	m[0].y = sin(angle);
	m[1].x = -sin(angle);
	m[1].y = cos(angle);
}
