/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:14:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/03 14:30:21 by user42           ###   ########.fr       */
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
	t_list *ite;

	printf("R	 %f %f\n", rt->width, rt->height);
	printf("A	 %f			 %f %f %f\n", rt->scene.ambiant_light.intensity, rt->scene.ambiant_light.color.r, rt->scene.ambiant_light.color.g, rt->scene.ambiant_light.color.b);

	ite = rt->scene.camera;
	while (ite)
	{
		t_camera camera = *(t_camera*)ite->content;
		printf("c	%f %f %f	%f %f %f	%f\n", camera.position.x, camera.position.y, camera.position.z, camera.direction.x, camera.direction.y, camera.direction.z, camera.fov);
		ite = ite->next;
	}
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
		printf("sp	%f %f %f		%f		%f %f %f\n", sp.center.x, sp.center.y, sp.center.z, sp.diameter, sp.color.r, sp.color.g, sp.color.b);
		ite = ite->next;
	}
}

int	main(int ac, char **av)
{
	t_rt rt;

	if (ac == 2)
	{
		rt = set_rt(av[1]);
		print_rt(&rt);
		set_mlx(&rt);
	}
	return (0);
}
