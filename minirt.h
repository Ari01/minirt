/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <denis.c1@live.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:34:57 by dchheang          #+#    #+#             */
/*   Updated: 2020/12/12 18:58:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <stdlib.h>
# include <math.h>

# define ESCAPE 65307

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
}				t_rt;

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

typedef struct	s_sphere
{
	t_vector	center;
	t_color		color;
	double		radius;
}				t_sphere;

typedef struct	s_ray
{
	t_vector start;
	t_vector dir;
}				t_ray;

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

int				exit_prog(t_rt *rt);
int				get_key_press(int key, t_rt *rt);
int				mouse_press(int button, int x, int y, t_rt *rt);
int				mouse_release(int button, int x, int y, t_rt *rt);
int				get_mouse_pos(int x, int y, t_rt *rt);

void			img_pixel_put(t_rt *rt, int x, int y, int color);

t_sphere		new_sphere(t_vector center, double radius);
void			print_sphere(t_rt *rt, t_sphere sp, t_camera camera);

t_vector		new_vector(double x, double y, double z);
t_vector		vectorAdd(t_vector v1, t_vector v2);
t_vector		vectorSub(t_vector v1, t_vector v2);
t_vector		vectorScale(double scalar, t_vector v);
double			vectorMul(t_vector v1, t_vector v2);

int				get_normal(t_vector *normal, t_vector new_start, t_vector sp_center);

t_ray			new_ray(t_vector start, t_vector dir);

t_camera		new_camera(t_ray ray, int fov);

t_color			new_color(int r, int b, int g);
int				color_to_trgb(t_color color);

t_light			new_light(t_vector pos, t_color color, double intensity);
t_color			get_light_value(t_light light, t_vector new_start, t_vector normal);

#endif
