/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 14:25:18 by user42            #+#    #+#             */
/*   Updated: 2020/12/14 17:42:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_vector start, t_vector dir)
{
	t_ray r;

	r.start = start;
	r.dir = dir;
	return (r);
}

int		get_normal(t_vector *normal, t_vector new_start, t_vector sp_center)
{
	double tmp;

	*normal = vectorSub(new_start, sp_center);
	tmp = vectorMul(*normal, *normal);
	if (tmp == 0)
		return (0);
	tmp = 1.0f / sqrtf(tmp);
	*normal = vectorScale(tmp, *normal);
	return (1);
}
