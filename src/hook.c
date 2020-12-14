/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:08:41 by user42            #+#    #+#             */
/*   Updated: 2020/12/11 13:47:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "stdio.h"
int		exit_prog(t_rt *rt)
{
	printf("exit\n");
	mlx_clear_window(rt->mlx, rt->window);
	mlx_destroy_window(rt->mlx, rt->window);
	mlx_destroy_image(rt->mlx, rt->img.img);
	//free(rt);
	exit(EXIT_SUCCESS);
}

int		get_key_press(int key, t_rt *rt)
{
	if (key == ESCAPE)
		exit_prog(rt);
	return (1);
}

int		mouse_press(int button, int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	(void)button;
	(void)rt;

	printf("mouse press\n");
	return (0);
}

int		mouse_release(int button, int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	(void)button;
	(void)rt;

	printf("mouse release\n");
	return (0);
}

int		get_mouse_pos(int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	(void)rt;
	printf("mouse pos\n");
	return (0);
}
