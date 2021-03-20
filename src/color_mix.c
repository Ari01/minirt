/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:13:40 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:16:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	color_add(t_color c1, t_color c2)
{
	t_color	color;

	color.r = c1.r + c2.r;
	color.g = c1.g + c2.g;
	color.b = c1.b + c2.b;
	return (color);
}

t_color	color_mix(t_color c1, t_color c2)
{
	t_color	c;

	c.r = 255 - ((255 - c1.r) + (255 - c2.r));
	c.g = 255 - ((255 - c1.g) + (255 - c2.g));
	c.b = 255 - ((255 - c1.b) + (255 - c2.b));
	return (c);
}
