/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_viewray_intersection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:09:22 by user42            #+#    #+#             */
/*   Updated: 2020/12/14 17:18:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*get_intersected_object(t_holder *holder, double *intersection)
{
	int i;
	void *current_object;

	current_object = NULL;
	i = 0;
	while (i < 3)
	{
		if (intersect_ray_sphere(holder->camera->viewray, holder->sphere[i], intersection))
			current_object = &holder->sphere[i];
		i++;
	}
	return (current_object);
}
