/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 06:31:09 by user42            #+#    #+#             */
/*   Updated: 2020/12/27 08:59:36 by user42           ###   ########.fr       */
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
	double		fov;
}				t_camera;

/*
**	GEOMETRIC FIGURES
*/
typedef struct	s_sphere
{
	t_vector	center;
	double		diameter;
	t_color		color;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	position;
	t_vector	direction;
	t_color		color;
}				t_plane;

typedef struct	s_square
{
	t_vector	position;
	t_vector	direction;
	double		height;
	t_color		color;
}				t_square;

typedef struct	s_cylindre
{
	t_vector	position;
	t_vector	direction;
	double		diameter;
	double		height;
	t_color		color;
}				t_cylindre;

typedef struct	s_triangle
{
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
	t_color		color;
}				t_triangle;

// object id ??
typedef struct	s_object
{
	void	*ptr;
	int		(*intersect)(t_camera, void *);
}				t_object;

/*
**	RT
*/

typedef struct	s_scene
{
	t_ambiant_light	ambiant_light;
	t_list			*light;
	t_list			*camera;
	t_list			*objects;
}				t_scene;

typedef struct	s_rt
{
	double	width;
	double	height;
	t_scene	scene;
}				t_rt;

#endif
