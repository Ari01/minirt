/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:15:21 by user42            #+#    #+#             */
/*   Updated: 2021/01/02 15:03:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "get_next_line.h"
# include "types.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <math.h>

# define ELEM_ID_SET "R,A,c,l,sp,pl,sq,cy,tr"
# define MAX(x,y)	(x) > (y) ? x : y
# define MIN(x,y)	(x) < (y) ? x : y

# define ESCAPE 65307
# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363

// rt
t_rt				init_rt();
void				free_rt(t_rt *rt);
void				set_mlx(t_rt *rt);

// hook
int					exit_prog(t_rt *rt);
int					key_hook(int key, t_rt *rt);

// scene
t_scene				init_scene();

// light
t_ambiant_light		init_ambiant_light();

// camera

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
// set_objects
int					set_sphere(char **split, t_rt *rt);
int					set_plane(char **split, t_rt *rt);
int					set_triangle(char **split, t_rt *rt);
int					set_cylindre(char **split, t_rt *rt);
int					set_square(char **split, t_rt *rt);
// parser
t_rt				set_rt(char *pathfile);

#endif
