/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:32 by user42            #+#    #+#             */
/*   Updated: 2020/12/27 09:03:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera	new_camera(t_vector pos, t_vector dir, double fov)
{
	t_camera c;

	c.position = pos;
	c.direction = dir;
	c.fov = fov;
	return (c);
}
