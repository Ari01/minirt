/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:32 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 18:45:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		set_camera_matrix(t_camera *camera)
{
	t_vector right;
	t_vector up;

	right = vector_cross(new_vector(0, 1, 0), camera->direction);
	up = vector_cross(camera->direction, right);
	camera->to_world_matrix[0] = right;
	camera->to_world_matrix[1] = up;
	camera->to_world_matrix[2] = camera->direction;
	camera->to_world_matrix[3] = new_vector(camera->position.x,
											camera->position.y,
											camera->position.z);
	matrix_cpy(camera->to_cam_matrix, camera->to_world_matrix);
	matrix_invert(camera->to_cam_matrix);
}

void		add_camera(t_rt *rt, t_camera *camera)
{
	set_camera_matrix(camera);
	if (rt->scene.camera == NULL)
		rt->camera = camera;
	ft_lstadd_front(&rt->scene.camera, ft_lstnew(camera));
}

void		compute_camera(t_rt *rt, double x, double y)
{
	double		aspect_ratio;
	double		scale;
	double		max;
	double		min;
	t_vector	pworld;

	max = MAX(rt->width, rt->height);
	min = MIN(rt->width, rt->height);
	aspect_ratio = max / min;
	scale = tan(M_PI * rt->camera->fov * 0.5 / 180);
	x = ((2 * (x + 0.5) / rt->width) - 1) * scale;
	y = (1 - 2 * (y + 0.5) / rt->height) * scale;
	if (rt->width >= rt->height)
		x *= aspect_ratio;
	else
		y *= aspect_ratio;
	pworld = new_vector(x, y, 1);
	pworld = vector_matrix_mul(pworld, rt->camera->to_world_matrix);
	rt->camera->direction = vector_sub(pworld, rt->camera->position);
	rt->camera->direction = vector_mul(1 / vector_len(rt->camera->direction),
										rt->camera->direction);
}
