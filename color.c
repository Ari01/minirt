/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:22:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 12:08:23 by user42           ###   ########.fr       */
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
/*
t_color	color_mix(t_color c1, t_color c2)
{
	t_hls	hls;
	t_hls	hls1;
	t_hls	hls2;
	double	x;
	double	y;

	hls1 = rgb_to_hls(c1);
	hls2 = rgb_to_hls(c2);
	hls.s = (hls1.s + hls2.s) * 0.5;
	hls.l = (hls1.l + hls2.l) * 0.5;
	x = cos(2 * M_PI * hls1.h) + cos(2 * M_PI * hls2.h);
	y = sin(2 * M_PI * hls1.h) + sin(2 * M_PI * hls2.h);
	if (x != 0.0 || y != 0.0)
		hls.h = atan2(y, x) / (2 * M_PI);
	else
	{
		hls.h = 0;
		hls.s = 0;
	}
	printf("hls = %f %f %f\n", hls.h, hls.l, hls.s);
	t_color color = hls_to_rgb(hls);
	printf("hls_to_rgb = %f %f %f\n", color.r, color.g, color.b);
	return (hls_to_rgb(hls));
}*/

t_color	color_mix(t_color c1, t_color c2)
{
	t_color	c;

	c.r = 255 - ((255 - c1.r) + (255 - c2.r));
	c.g = 255 - ((255 - c1.g) + (255 - c2.g));
	c.b = 255 - ((255 - c1.b) + (255 - c2.b));
	return (c);
}

t_color	color_scale(double x, t_color color)
{
	color.r *= x;
	color.g *= x;
	color.b *= x;
	return (color);
}

t_color	color_mul(t_color c1, t_color c2)
{
	t_color	c;

	c.r = c1.r * c2.r;
	c.g = c1.g * c2.g;
	c.b = c1.b * c2.b;
	return (c);
}

t_color	color_clamp(t_color color)
{
	color.r = MIN(255, MAX(0, color.r));
	color.g = MIN(255, MAX(0, color.g));
	color.b = MIN(255, MAX(0, color.b));
	return (color);
}
