/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 07:10:25 by user42            #+#    #+#             */
/*   Updated: 2021/01/02 08:53:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	img_pixel_put(t_rt *rt, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= rt->width || y < 0 || y >= rt->height)
		return ;
	dst = rt->img.addr + (y * rt->img.line_length + x *(rt->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
/*
void	render(t_rt *rt)
{
	double	aspect_ratio;
	double	x;
	double	y;
	int		i;
	int		j;

	j = 0;
	while (j < rt->height)
	{
		i = 0;
		while (i < rt->width)
		{
			x = (2 * ((i + 0.5) / rt->width) - 1) * tan()
			i++;
		}
		j++;
	}
}*/	
