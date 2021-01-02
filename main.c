/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:14:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/02 15:54:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	test_func(void *object_ptr)
{
	t_sphere sp;

	sp = *(t_sphere *)object_ptr;
	printf("sp.center = %f %f %f, sp.diameter = %f, sp.color = %f %f %f\n",
	sp.center.x, sp.center.y, sp.center.z, sp.diameter, sp.color.r, sp.color.g, sp.color.b);
}

void	print_rt(t_rt *rt)
{
	printf("R	 %f %f\n", rt->width, rt->height);
	printf("A	 %f			 %f %f %f\n", rt->scene.ambiant_light.intensity, rt->scene.ambiant_light.color.r, rt->scene.ambiant_light.color.g, rt->scene.ambiant_light.color.b);

	while (rt->scene.camera)
	{
		t_camera camera = *(t_camera*)rt->scene.camera->content;
		printf("c	%f %f %f	%f %f %f	%f\n", camera.position.x, camera.position.y, camera.position.z, camera.direction.x, camera.direction.y, camera.direction.z, camera.fov);
		rt->scene.camera = rt->scene.camera->next;
	}
	while (rt->scene.light)
	{
		t_light light = *(t_light*)rt->scene.light->content;
		printf("l	%f %f %f	%f		%f %f %f\n", light.position.x, light.position.y, light.position.z, light.intensity, light.color.r, light.color.g, light.color.b);
		rt->scene.light = rt->scene.light->next;
	}
	while (rt->scene.objects)
	{
		t_object object = *(t_object*)rt->scene.objects->content;
		t_sphere sp = *(t_sphere*)object.ptr;
		printf("sp	%f %f %f		%f		%f %f %f\n", sp.center.x, sp.center.y, sp.center.z, sp.diameter, sp.color.r, sp.color.g, sp.color.b);
		rt->scene.objects = rt->scene.objects->next;
	}
}

int	main(int ac, char **av)
{
	t_rt rt;

	if (ac == 2)
	{
		rt = set_rt(av[1]);
	//	print_rt(&rt);
	//	set_mlx(&rt);
		exit_prog(&rt);
	}
	return (0);
}
