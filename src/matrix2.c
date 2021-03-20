/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:58:55 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 20:00:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		get_matrix_det(t_vector *m)
{
	double	left;
	double	right;

	left = m[0].x * m[1].y * m[2].z
			+ m[1].x * m[2].y * m[0].z
			+ m[2].x * m[0].y * m[1].z;
	right = m[2].x * m[1].y * m[0].z
			+ m[1].x * m[0].y * m[2].z
			+ m[0].x * m[2].y * m[1].z;
	return (left - right);
}

void		matrix_invert(t_vector *m)
{
	double		det;
	t_vector	tmp[3];

	det = get_matrix_det(m);
	tmp[0].x = m[1].y * m[2].z - m[2].y * m[1].z / det;
	tmp[0].y = m[2].y * m[0].z - m[0].y * m[2].z / det;
	tmp[0].z = m[0].y * m[1].z - m[1].y * m[0].z / det;
	tmp[1].x = m[2].x * m[1].z - m[1].x * m[2].z / det;
	tmp[1].y = m[0].x * m[2].z - m[2].x * m[0].z / det;
	tmp[1].z = m[1].x * m[0].z - m[0].x * m[1].z / det;
	tmp[2].x = m[1].x * m[2].y - m[2].x * m[1].y / det;
	tmp[2].y = m[2].x * m[0].y - m[0].x * m[2].y / det;
	tmp[2].z = m[0].x * m[1].y - m[1].x * m[0].y / det;
	matrix_cpy(m, tmp);
}
