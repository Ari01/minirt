/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:35:45 by user42            #+#    #+#             */
/*   Updated: 2020/12/14 18:27:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

/*
** SPHERE
*/
t_sphere		new_sphere(t_vector pos, double radius, t_color color);
int				get_intersection(double a, double b, double discriminant, double *intersection);
int				intersect_ray_sphere(t_ray ray, t_sphere sp, double *intersection);

/*
** VECTOR
*/
t_vector		new_vector(double x, double y, double z);
t_vector		vectorAdd(t_vector v1, t_vector v2);
t_vector		vectorSub(t_vector v1, t_vector v2);
t_vector		vectorScale(double scalar, t_vector v);
double			vectorMul(t_vector v1, t_vector v2);

/*
** RAY
*/
t_ray			new_ray(t_vector start, t_vector dir);
int				get_normal(t_vector *normal, t_vector new_start, t_vector sp_center);

/*
** OBJECT INTERSECTION
*/
void			*get_intersected_object(t_holder *holder, double *intersection);

#endif
