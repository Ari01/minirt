/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:22:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/10 05:35:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	new_color(double r, double g, double b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

int		color_to_trgb(t_color color)
{
	return (0 << 24 | (int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

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
	t_color	color;

	color.r = (c1.r + c2.r) / 2;
	color.g = (c1.g + c2.g) / 2;
	color.b = (c1.b + c2.b) / 2;
	return (color);
}

t_color	color_mul(double x, t_color color)
{
	color.r *= x;
	color.g *= x;
	color.b *= x;
	return (color);
}

t_color	color_clamp(t_color color)
{
	color.r = MIN(255, MAX(0, color.r));
	color.g = MIN(255, MAX(0, color.g));
	color.b = MIN(255, MAX(0, color.b));
	return (color);
}
