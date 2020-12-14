/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:14:41 by user42            #+#    #+#             */
/*   Updated: 2020/12/14 18:39:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*
** MLX
*/
typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_rt
{
	void		*mlx;
	void		*window;
	t_img		img;
	int			width;
	int			height;
}				t_rt;

/*
** COLOR AND GEOMETRIC OBJECTS
*/
typedef struct	s_color
{
	double	red;
	double	green;
	double	blue;
}				t_color;

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

typedef struct	s_sphere
{
	t_vector	pos;
	t_color		color;
	double		radius;
}				t_sphere;

/*
** CAM, LIGHT, HOLDER
*/
typedef struct	s_camera
{
	t_ray	viewray;
	int		fov;
}				t_camera;

typedef struct	s_light
{
	t_vector	pos;
	t_color		color;
	double		intensity;
}				t_light;

typedef struct	s_holder
{
	t_light		*light;
	t_sphere	*sphere;
	t_camera	*camera;
	t_color		current_color;
}				t_holder;

#endif
