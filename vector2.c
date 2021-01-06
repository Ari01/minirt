/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 07:07:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 12:14:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector4	new_vector4(double x, double y, double z, double w)
{
	t_vector4 v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
}

double		vector_len(t_vector v)
{
	return (sqrtf(vector_dot(v, v)));
}
