/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:26:41 by user42            #+#    #+#             */
/*   Updated: 2020/12/14 17:56:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>
t_rt	*new_window(int width, int height, char *title)
{
	t_rt *rt;

	rt = malloc(sizeof(*rt));
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (NULL);
	rt->window = mlx_new_window(rt->mlx, width, height, title);
	if (!rt->window)
		return (NULL);
	rt->width = width;
	rt->height = height;
	return (rt);
}

void	wait_event(t_rt *rt)
{
	mlx_hook(rt->window, 33, 1L<<0, &exit_prog, rt);
	mlx_hook(rt->window, 2, 1L<<0, &get_key_press, rt);
	mlx_loop(rt->mlx);
}

int		main()
{
	t_rt		*rt;
	t_holder	holder;
	t_sphere	sphere[3];
	t_light		light[3];
	t_camera	camera;

	rt = new_window(800, 600, "minirt");
	if (!rt)
		return (0);
	rt->img.img = mlx_new_image(rt->mlx, 800, 600);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
								&rt->img.line_length, &rt->img.endian);
	sphere[0] = new_sphere(new_vector(200, 300, 0), 100.0, new_color(1.0, 0, 0));
	sphere[1] = new_sphere(new_vector(400, 400, 0), 100.0, new_color(0, 1.0, 0));
	sphere[2] = new_sphere(new_vector(500, 140, 0), 100.0, new_color(0, 0, 1.0));
	light[0] = new_light(new_vector(0, 240, -100), new_color(1.0, 1.0, 1.0), 1.0);
	light[1] = new_light(new_vector(3200, 3000, -1000), new_color(0.6, 0.7, 1.0), 0.7);
	light[2] = new_light(new_vector(600, 0, -100), new_color(0.3, 0.5, 1.0), 0.9);
	camera = new_camera(new_ray(new_vector(0, 0, -2000), new_vector(0, 0, 1)), 70);
	holder.sphere = sphere;
	holder.light = light;
	holder.camera = &camera;
	print_object(rt, &holder);
	mlx_put_image_to_window(rt->mlx, rt->window, rt->img.img, 0, 0);
	wait_event(rt);
	return (0);
}
