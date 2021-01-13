/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:11:56 by user42            #+#    #+#             */
/*   Updated: 2021/01/13 16:30:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move_object(int key, t_rt *rt)
{
/*	double x;
	double y;
	double z;
*/
	if (key == 'q')
		rt->object->position.x--;
	if (key == 'd')
		rt->object->position.x++;
	if (key == 'z')
		rt->object->position.z++;
	if (key == 's')
		rt->object->position.z--;
	if (key == CONTROL)
		rt->object->position.y--;
	if (key == SPACE)
		rt->object->position.y++;
}
