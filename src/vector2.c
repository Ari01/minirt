/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 07:07:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 10:07:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}

double		vector_len(t_vector v)
{
	return (sqrtf(vector_dot(v, v)));
}

t_vector	vector_normalize(t_vector v)
{
	return (vector_mul(1 / vector_len(v), v));
}
