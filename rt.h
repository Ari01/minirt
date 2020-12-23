/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 02:39:10 by user42            #+#    #+#             */
/*   Updated: 2020/12/23 10:10:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mlx.h"
# include <math.h>
# include <stdlib.h>

# define min(x,y)	((x) < (y) ? (x) : (y))
# define max(x,y)	((x) > (y) ? (x) : (y))

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
	void	*mlx;
	void	*window;
	t_img	img;
	int		width;
	int		height;
}				t_rt;

typedef struct	s_viewport
{
	double width;
	double height;
	double distance;
}				t_viewport;

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct	s_color
{
	double r;
	double g;
	double b;
}				t_color;

typedef struct	s_sphere
{
	t_vector	center;
	double		radius;
	t_color		color;
	double		specular;
}				t_sphere;

typedef struct	s_light
{
	t_vector	pos;
	double		intensity;
	t_color		color;
}				t_light;

typedef struct	s_scene
{
	t_sphere	*sphere;
	t_light		*light;
	t_ray		viewray;
}				t_scene;