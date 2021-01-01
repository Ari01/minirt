/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:15:21 by user42            #+#    #+#             */
/*   Updated: 2021/01/01 14:49:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "get_next_line.h"
# include "types.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>

# define ELEM_ID_SET "R,A,c,l,sp,pl,sq,cy,tr"

t_rt				init_rt();
t_scene				init_scene();
t_ambiant_light		init_ambiant_light();

t_color				new_color(double r, double g, double b);
t_vector			new_vector(double x, double y, double z);

void				print_error_msg(char *msg);

// parser utils
void				string_array_free(char **split);
int					set_color(char **split, t_color *color);
int					set_coord(char **split, t_vector *coord);
int					correct_direction(t_vector dir);
// set_scene
void				set_resolution(char **split, t_rt *rt);
void				set_ambiant_light(char **split, t_rt *rt);
void				set_camera(char **split, t_rt *rt);
void				set_light(char **split, t_rt *rt);
// set_objects
void				set_sphere(char **split, t_rt *rt);
void				set_plane(char **split, t_rt *rt);
void				set_triangle(char **split, t_rt *rt);
void				set_cylindre(char **split, t_rt *rt);
void				set_square(char **split, t_rt *rt);
// parser
t_rt				parse(char *pathfile);

#endif