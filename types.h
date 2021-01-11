/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 06:31:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 12:10:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*
** UTILS
*/
typedef struct	s_color
{
	double r;
	double g;
	double b;
}				t_color;

typedef struct	s_vector
{
	double x;
	double y;
	double z;
}				t_vector;

typedef struct	s_ray
{
	t_vector	pos;
	t_vector	dir;
}				t_ray;

/*
** LIGHT AND CAMERA
*/
typedef struct	s_ambiant_light
{
	double	intensity;
	t_color	color;
}				t_ambiant_light;

typedef struct	s_light
{
	t_vector	position;
	double		intensity;
	t_color		color;
}				t_light;

typedef struct	s_camera
{
	t_vector	position;
	t_vector	direction;
	t_vector	to_world_matrix[4];
	double		fov;
}				t_camera;

/*
**	GEOMETRIC FIGURES
*/
typedef struct	s_sphere
{
	double		diameter;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	direction;
}				t_plane;

typedef struct	s_square
{
	t_vector	direction;
	double		height;
}				t_square;

typedef struct	s_cylindre
{
	t_vector	direction;
	double		diameter;
	double		height;
}				t_cylindre;

typedef struct	s_triangle
{
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
}				t_triangle;

typedef struct	s_object
{
	void		*ptr;
	t_vector	position;
	t_color		color;
	double		specular;
	double		(*intersect)(t_ray, struct s_object *, double , double);
	t_vector	(*get_normal)(t_vector, struct s_object *);
}				t_object;

/*
**	SCENE
*/
typedef struct	s_scene
{
	t_ambiant_light	ambiant_light;
	t_list			*light;
	t_list			*camera;
	t_list			*objects;
}				t_scene;

/*
**	RT
*/
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
	double		width;
	double		height;
	t_scene		scene;
	t_camera	*camera;
	t_ray		ray;
}				t_rt;

#endif
