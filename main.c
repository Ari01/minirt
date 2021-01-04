/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:14:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/04 19:34:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_rt(t_rt *rt)
{
	t_list *ite;

	printf("R	 %f %f\n", rt->width, rt->height);
	printf("A	 %f			 %f %f %f\n", rt->scene.ambiant_light.intensity, rt->scene.ambiant_light.color.r, rt->scene.ambiant_light.color.g, rt->scene.ambiant_light.color.b);

/*	ite = rt->scene.camera;
	while (ite)
	{
		t_camera camera = *(t_camera*)ite->content;
		printf("c	%f %f %f	%f %f %f	%f\n", camera.position.x, camera.position.y, camera.position.z, camera.direction.x, camera.direction.y, camera.direction.z, camera.fov);
		ite = ite->next;
	}*/
	printf("c	%f %f %f	%f %f %f	%f\n", rt->camera->position.x, rt->camera->position.y, rt->camera->position.z, rt->camera->direction.x, rt->camera->direction.y, rt->camera->direction.z, rt->camera->fov);

	ite = rt->scene.light;
	while (ite)
	{
		t_light light = *(t_light*)ite->content;
		printf("l	%f %f %f	%f		%f %f %f\n", light.position.x, light.position.y, light.position.z, light.intensity, light.color.r, light.color.g, light.color.b);
		ite = ite->next;
	}
	ite = rt->scene.objects;
	while (ite)
	{
		t_object object = *(t_object*)ite->content;
		t_sphere sp = *(t_sphere*)object.ptr;
		printf("sp	%f %f %f		%f		%f %f %f\n", object.position.x, object.position.y, object.position.z, sp.diameter, object.color.r, object.color.g, object.color.b);
		ite = ite->next;
	}
}

int	main(int ac, char **av)
{
	t_rt rt;

	if (ac == 2)
	{
		rt = set_rt(av[1]);
		//print_rt(&rt);
		set_mlx(&rt);
		render(&rt);
		mlx_hook(rt.window, 33, 1L<<0, &exit_prog, &rt);
		mlx_hook(rt.window, 2, 1L<<0, &key_hook, &rt);
		mlx_loop(rt.mlx);
	}
	return (0);
}
