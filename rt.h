/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:15:21 by user42            #+#    #+#             */
/*   Updated: 2021/01/13 19:15:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "types.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <math.h>

# define MAX(x,y)	((x) > (y) ? (x) : (y))
# define MIN(x,y)	((x) < (y) ? (x) : (y))

/*
** PARSER
*/
# define ELEM_ID_SET "R,A,c,l,sp,pl,sq,cy,tr"

/*
** KEY CODE
*/
# define ESCAPE		65307
# define CONTROL	65507
# define TAB		65289
# define SPACE		32

/*
** TRANSFORMATION
*/
# define CAMERA		0
# define OBJECT		1
# define TRANSLATE	0
# define ROTATE		1
# define RAD		0.174533

// rt
t_rt				init_rt();
void				free_rt(t_rt *rt);
void				set_mlx(t_rt *rt);

// hook
int					exit_prog(t_rt *rt);
int					key_hook(int key, t_rt *rt);

// render
void				img_pixel_put(t_rt *rt, int x, int y, int color);
void				render(t_rt *rt);

// trace ray
int					resolve_quadratic(t_vector v, double *t1, double *t2);
double				get_closest_intersection(t_rt *rt, t_object **closest_object, double t_min, double t_max);
t_color				trace_ray(t_rt *rt);

// scene
t_scene				init_scene();

// light
t_ambiant_light		init_ambiant_light();
double				compute_light(t_rt *rt, t_object *object, t_vector intersection, t_vector normal);

// camera
t_vector			vector_matrix_mul(t_vector v, t_vector *matrix);
void				set_camera_matrix(t_camera *camera);
void				compute_camera(t_rt *rt, double x, double y);
void				move_camera(int key, t_rt *rt);
void				rotate_camera(int key, t_rt *rt);

// objects

void				move_object(int key, t_rt *rt);

// sphere
double				ray_sphere_intersect(t_ray ray, t_object *object, double t_min, double t_max);
t_vector			get_sphere_normal(t_vector intersection, t_object *object);

// plane
double				ray_plane_intersect(t_ray ray, t_object *object, double t_min, double t_max);
t_vector			get_plane_normal(t_vector intersection, t_object *object);
void				rotate_plane(int key, t_object *object);

// color
t_color				new_color(double r, double g, double b);
int					color_to_trgb(t_color color);
t_color				color_mul(double x, t_color color);
t_color				color_clamp(t_color color);

// vector
t_vector			new_vector(double x, double y, double z);
t_vector			vector_add(t_vector v1, t_vector v2);
t_vector			vector_sub(t_vector v1, t_vector v2);
t_vector			vector_mul(double x, t_vector v2);
double				vector_dot(t_vector v1, t_vector v2);
double				vector_len(t_vector v);

// matrix
t_vector			vector_matrix_mul(t_vector v, t_vector *matrix);
void				matrix_mul(t_vector *m1, t_vector *m2);

// error
void				ft_perror();
void				print_error_msg(char *msg);

// parser utils
void				string_array_free(char **split);
int					set_color(char **split, t_color *color);
int					set_coord(char **split, t_vector *coord);
int					correct_direction(t_vector dir);
// set_scene
int					set_resolution(char **split, t_rt *rt);
int					set_ambiant_light(char **split, t_rt *rt);
int					set_camera(char **split, t_rt *rt);
int					set_light(char **split, t_rt *rt);
int					set_scene(char *line, char **split, t_rt *rt);
// set_objects
int					set_sphere(char **split, t_rt *rt);
int					set_plane(char **split, t_rt *rt);
int					set_triangle(char **split, t_rt *rt);
int					set_cylindre(char **split, t_rt *rt);
int					set_square(char **split, t_rt *rt);
// parser
t_rt				set_rt(char *pathfile);

#endif
