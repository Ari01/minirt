/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:14:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/01 14:57:55 by user42           ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_rt rt;

	if (ac == 2)
	{
		rt = parse(av[1]);
		printf("res = %f %f\n", rt.width, rt.height);
		int i = 0;
		while (rt.scene.objects)
		{
			i++;
			rt.scene.objects = rt.scene.objects->next;
		}
		printf("number of objects = %d\n", i);
	}
	return (0);
}
