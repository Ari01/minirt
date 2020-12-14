/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:00:46 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 17:37:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		new_color(double r, double g, double b)
{
	t_color c;

	c.red = r;
	c.green = g;
	c.blue = b;
	return (c);
}

int			color_to_trgb(t_color color)
{
	return (0 << 24 | (int)color.red << 16 | (int)color.green << 8 | (int)color.blue);
}
