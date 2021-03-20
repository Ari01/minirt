/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:34:19 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 07:41:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		matrix_cpy(t_vector *dst, t_vector *src)
{
	int i;

	i = 0;
	while (i < 3)
	{
		dst[i] = src[i];
		i++;
	}
}

t_vector	vector_matrix_mul(t_vector v, t_vector *matrix)
{
	t_vector	mul;

	mul.x = v.x * matrix[0].x
			+ v.y * matrix[1].x
			+ v.z * matrix[2].x
			+ matrix[3].x;
	mul.y = v.x * matrix[0].y
			+ v.y * matrix[1].y
			+ v.z * matrix[2].y
			+ matrix[3].y;
	mul.z = v.x * matrix[0].z
			+ v.y * matrix[1].z
			+ v.z * matrix[2].z
			+ matrix[3].z;
	return (mul);
}

t_vector	dir_matrix_mul(t_vector v, t_vector *matrix)
{
	t_vector	mul;

	mul.x = v.x * matrix[0].x + v.y * matrix[1].x + v.z * matrix[2].x;
	mul.y = v.x * matrix[0].y + v.y * matrix[1].y + v.z * matrix[2].y;
	mul.z = v.x * matrix[0].z + v.y * matrix[1].z + v.z * matrix[2].z;
	return (mul);
}

void		matrix_mul(t_vector *m1, t_vector *m2)
{
	int			i;
	t_vector	mul[3];

	i = 0;
	while (i < 3)
	{
		mul[i].x = m1[0].x * m2[i].x
					+ m1[1].x * m2[i].y
					+ m1[2].x * m2[i].z;
		mul[i].y = m1[0].y * m2[i].x
					+ m1[1].y * m2[i].y
					+ m1[2].y * m2[i].z;
		mul[i].z = m1[0].z * m2[i].x
					+ m1[1].z * m2[i].y
					+ m1[2].z * m2[i].z;
		i++;
	}
	matrix_cpy(m1, mul);
}
