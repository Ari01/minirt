/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hls.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:54:51 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 15:52:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hls		rgb_to_hls(t_color c)
{
	t_hls	hls;
	double	cmax;
	double	cmin;
	double	delta;


	c = color_scale(1.0 / 255.0, c);
	cmax = MAX(c.r, MAX(c.g, c.b));
	cmin = MIN(c.r, MIN(c.g, c.b));
	delta = cmax - cmin;
	hls.l = (cmax + cmin) / 2.0;
	if (!delta)
	{
		hls.h = 0;
		hls.s = 0;
		return (hls);
	}
	else
	{
		hls.s = delta / (1 - fabs(2 * hls.l - 1));
		if (cmax == c.r)
			hls.h = ((int)(c.g - c.b / delta) % 6) * 60.0;
		else if (cmax == c.g)
			hls.h = ((c.b - c.r / delta) + 2.0) * 60.0;
		else
			hls.h = ((c.r - c.g / delta) + 4.0) * 60.0;
	}
	return (hls);
}

t_color		hls_to_rgb(t_hls hls)
{
	double	c;
	double	x;
	double	m;
	t_color	color;

	c = (1 - fabs(2 * hls.l - 1)) * hls.s;
	x = c * (1 - abs((int)(hls.h / 60) % 2 - 1));
	m = hls.l - c / 2;
	if (hls.h < 60)
		color = new_color(c, x, 0);
	else if (hls.h < 120)
		color = new_color(x, c, 0);
	else if (hls.h < 180)
		color = new_color(0, c, x);
	else if (hls.h < 240)
		color = new_color(0, x, c);
	else if (hls.h < 300)
		color = new_color(x, 0, c);
	else
		color = new_color(c, 0, x);
	color.r += m;
	color.b += m;
	color.g += m;
	color = color_scale(255, color);
	return (color);
}
