/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <denis.c1@live.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:34:57 by dchheang          #+#    #+#             */
/*   Updated: 2020/12/14 18:24:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "types.h"
# include "object.h"
# include <stdlib.h>
# include <math.h>

# define ESCAPE 65307
# define min(x, y)	((x) < (y) ? (x) : (y))

/*
** HOOK
*/
int				exit_prog(t_rt *rt);
int				get_key_press(int key, t_rt *rt);
int				mouse_press(int button, int x, int y, t_rt *rt);
int				mouse_release(int button, int x, int y, t_rt *rt);
int				get_mouse_pos(int x, int y, t_rt *rt);

/*
** COLOR
*/
t_color			new_color(double r, double b, double g);
int				color_to_trgb(t_color color);

/*
** CAMERA
*/
t_camera		new_camera(t_ray ray, int fov);

/*
** LIGHT
*/
t_light			new_light(t_vector pos, t_color color, double intensity);
t_color			get_light_value(t_holder *holder, t_sphere sp, t_vector new_start, t_vector normal);

/*
** PRINT
*/
void			print_object(t_rt *rt, t_holder *holder);

#endif
