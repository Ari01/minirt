/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:16:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/01 20:42:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		exit_prog(t_rt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img.img);
	mlx_clear_window(rt->mlx, rt->window);
	mlx_destroy_window(rt->mlx, rt->window);
	exit(EXIT_SUCCESS);
}

int		key_hook(int key, t_rt *rt)
{
	if (key == ESCAPE)
		exit_prog(rt);
	return (0);
}
