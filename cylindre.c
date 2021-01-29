/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:26:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 19:03:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		ray_cylindre_intersect(t_ray ray, t_object *object, double t_min, double t_max)
{
	double		t;
	double		discriminant;
	t_vector	quadratic;

	t_cylindre	cylindre;
	cylindre = *(t_cylindre *)object->ptr;
	quadratic.x = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
}
