/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:30:00 by user42            #+#    #+#             */
/*   Updated: 2020/12/15 18:40:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "mlx.h"
# include <math.h>
# include <stdlib.h>

# define min(x,y)	((x) < (y) ? (x) : (y))

typedef struct	s_vector
{
	double x;
	double y;
	double z;
}				t_vector;

typedef struct	s_ray
{
	t_vector start;
	t_vector dir;
}				t_ray;

typedef struct	s_color
{
	double r;
	double g;
	double b;
}				t_color;

typedef struct	s_sphere
{
	t_vector	pos;
	double		radius;
	t_color		color;
}				t_sphere;

typedef	struct	s_viewport
{
	int		width;
	int		height;
	double	distance;
}				t_viewport;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_rt
{
	void		*mlx;
	void		*window;
	t_img		img;
	int			width;
	int			height;
	t_viewport	viewport;
}				t_rt;

typedef struct	s_light
{
	t_vector	pos;
	t_color		color;
	double		intensity;
}				t_light;

#endif
